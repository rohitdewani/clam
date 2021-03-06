/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2013, CU Boulder
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of CU Boulder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/**
 * \brief   Simple pick place for blocks using ClamArm
 * \author  Dave Coleman
 */

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

// Clam
#include <clam_msgs/ClamGripperCommandAction.h>

// MoveIt!
#include <moveit/move_group_interface/move_group.h>
#include <shape_tools/solid_primitive_dims.h>

// Grasp generation
#include <block_grasp_generator/block_grasp_generator.h>
#include <block_grasp_generator/robot_viz_tools.h> // simple tool for showing grasps

static const std::string ROBOT_DESCRIPTION="robot_description";
static const std::string RVIZ_MARKER_TOPIC = "/end_effector_marker";
static const std::string PLANNING_GROUP_NAME = "arm";
static const std::string BASE_LINK = "/base_link";
static const std::string EE_GROUP = "gripper_group";
static const std::string EE_JOINT = "gripper_finger_joint";
static const std::string EE_PARENT_LINK = "gripper_roll_link";
static const std::string BLOCK_NAME = "block";
static const double BLOCK_SIZE = 0.04;

// class for publishing stuff to rviz
block_grasp_generator::RobotVizToolsPtr rviz_tools_;

// grasp generator
block_grasp_generator::BlockGraspGeneratorPtr block_grasp_generator_;

// publishers
ros::Publisher pub_co_;
ros::Publisher pub_aco_;

// data for generating grasps
block_grasp_generator::RobotGraspData grasp_data_;

// our interface with MoveIt
boost::scoped_ptr<move_group_interface::MoveGroup> group_;

// block description
typedef std::pair<std::string,geometry_msgs::Pose> MetaBlock;


void loadRobotGraspData()
{
  // -------------------------------
  // Create pre-grasp posture
  grasp_data_.pre_grasp_posture_.header.frame_id = BASE_LINK;
  grasp_data_.pre_grasp_posture_.header.stamp = ros::Time::now();
  // Name of joints:
  grasp_data_.pre_grasp_posture_.name.resize(1);
  grasp_data_.pre_grasp_posture_.name[0] = EE_JOINT;
  // Position of joints
  grasp_data_.pre_grasp_posture_.position.resize(1);
  grasp_data_.pre_grasp_posture_.position[0] = clam_msgs::ClamGripperCommandGoal::GRIPPER_OPEN;

  // -------------------------------
  // Create grasp posture
  grasp_data_.grasp_posture_.header.frame_id = BASE_LINK;
  grasp_data_.grasp_posture_.header.stamp = ros::Time::now();
  // Name of joints:
  grasp_data_.grasp_posture_.name.resize(1);
  grasp_data_.grasp_posture_.name[0] = EE_JOINT;
  // Position of joints
  grasp_data_.grasp_posture_.position.resize(1);
  grasp_data_.grasp_posture_.position[0] = clam_msgs::ClamGripperCommandGoal::GRIPPER_CLOSE;

  // -------------------------------
  // Links
  grasp_data_.base_link_ = BASE_LINK;
  grasp_data_.ee_parent_link_ = EE_PARENT_LINK;
  ROS_ERROR_STREAM_NAMED("","EE parent link = " << EE_PARENT_LINK);

  // -------------------------------
  // Nums
  grasp_data_.approach_retreat_desired_dist_ = 0.05;
  grasp_data_.approach_retreat_min_dist_ = 0.025;
}

double fRand(double fMin, double fMax)
{
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}

void generateRandomBlock(geometry_msgs::Pose& block_pose)
{
  // Position
  block_pose.position.x = fRand(0.1,0.45);
  //  block_pose.position.y = fRand(-0.25,0.25);
  block_pose.position.y = fRand(-0.25,-0.05);
  block_pose.position.z = 0.02;

  // Orientation
  double angle = M_PI * fRand(0.1,1);
  Eigen::Quaterniond quat(Eigen::AngleAxis<double>(double(angle), Eigen::Vector3d::UnitZ()));
  block_pose.orientation.x = quat.x();
  block_pose.orientation.y = quat.y();
  block_pose.orientation.z = quat.z();
  block_pose.orientation.w = quat.w();
}

void publishCollisionBlock(geometry_msgs::Pose block_pose, std::string block_name)
{
  moveit_msgs::CollisionObject co;
  co.header.stamp = ros::Time::now();
  co.header.frame_id = BASE_LINK;
  co.id = block_name;
  co.operation = moveit_msgs::CollisionObject::ADD;
  co.primitives.resize(1);
  co.primitives[0].type = shape_msgs::SolidPrimitive::BOX;
  co.primitives[0].dimensions.resize(shape_tools::SolidPrimitiveDimCount<shape_msgs::SolidPrimitive::BOX>::value);
  co.primitives[0].dimensions[shape_msgs::SolidPrimitive::BOX_X] = BLOCK_SIZE;
  co.primitives[0].dimensions[shape_msgs::SolidPrimitive::BOX_Y] = BLOCK_SIZE;
  co.primitives[0].dimensions[shape_msgs::SolidPrimitive::BOX_Z] = BLOCK_SIZE;
  co.primitive_poses.resize(1);
  co.primitive_poses[0] = block_pose;
  pub_co_.publish(co);
}

bool pick(const geometry_msgs::Pose& block_pose, std::string block_name)
{
  ROS_WARN_STREAM_NAMED("","picking block "<< block_name);

  std::vector<manipulation_msgs::Grasp> grasps;

  // Pick grasp
  block_grasp_generator_->generateGrasps( block_pose, grasp_data_, grasps );

  // Prevent collision with table
  group_->setSupportSurfaceName("tabletop_link");

  //ROS_WARN_STREAM_NAMED("","testing grasp 1:\n" << grasps[0]);

  //ROS_INFO_STREAM_NAMED("","Grasp 0\n" << grasps[0]);
  //ROS_INFO_STREAM_NAMED("","\n\n\nGrasp 10\n" << grasps[10]);

  return group_->pick(block_name, grasps);
}

bool place(const MetaBlock block)
{
  ROS_WARN_STREAM_NAMED("","placing block "<< block.first);

  std::vector<manipulation_msgs::PlaceLocation> place_locations;
  std::vector<manipulation_msgs::Grasp> grasps;

  // Re-usable datastruct
  geometry_msgs::PoseStamped pose_stamped;
  pose_stamped.header.frame_id = BASE_LINK;
  pose_stamped.header.stamp = ros::Time::now();

  // Generate grasps
  block_grasp_generator_->generateGrasps( block.second, grasp_data_, grasps );

  // Convert 'grasps' to palce_locations format
  for (std::size_t i = 0; i < grasps.size(); ++i)
  {
    // Create new place location
    manipulation_msgs::PlaceLocation place_loc;

    // Pose
    pose_stamped.pose = grasps[i].grasp_pose.pose;
    place_loc.place_pose = pose_stamped;

    // Publish to Rviz
    rviz_tools_->publishArrow(pose_stamped.pose);

    // Approach & Retreat
    place_loc.approach = grasps[i].approach;
    //ROS_WARN_STREAM_NAMED("","is the same? \n" << place_loc.approach);
    place_loc.retreat = grasps[i].retreat;

    // Post place posture - use same as pre-grasp posture (the OPEN command_
    place_loc.post_place_posture = grasp_data_.pre_grasp_posture_;

    place_locations.push_back(place_loc);
  }
  ROS_INFO_STREAM_NAMED("pick_place","Created " << place_locations.size() << " place locations");

  // Prevent collision with table
  group_->setSupportSurfaceName("tabletop_link");

  group_->setPlannerId("RRTConnectkConfigDefault");

  return group_->place(block.first, place_locations);
}

void cleanupACO()
{
  // Clean up old attached collision object
  moveit_msgs::AttachedCollisionObject aco;
  aco.object.header.stamp = ros::Time::now();
  aco.object.header.frame_id = BASE_LINK;
  aco.object.operation = moveit_msgs::CollisionObject::REMOVE;
  aco.link_name = EE_PARENT_LINK;
  ros::WallDuration(0.5).sleep();
  pub_aco_.publish(aco);
  ros::WallDuration(0.5).sleep();
  pub_aco_.publish(aco);

}
void cleanupCO(std::string name)
{
  // Clean up old collision objects
  moveit_msgs::CollisionObject co;
  co.header.stamp = ros::Time::now();
  co.header.frame_id = BASE_LINK;
  co.id = name;
  co.operation = moveit_msgs::CollisionObject::REMOVE;
  ros::WallDuration(0.5).sleep();
  pub_co_.publish(co);
  ros::WallDuration(0.5).sleep();
  pub_co_.publish(co);
}

void getGoalBlocks(std::vector<MetaBlock>& block_locations)
{
  // Position
  geometry_msgs::Pose block_pose;
  block_pose.position.x = 0.3;
  block_pose.position.y = 0.2;
  block_pose.position.z = BLOCK_SIZE/2 * 0.9;

  // Orientation
  double angle = M_PI / 1.5;
  Eigen::Quaterniond quat(Eigen::AngleAxis<double>(double(angle), Eigen::Vector3d::UnitZ()));
  block_pose.orientation.x = quat.x();
  block_pose.orientation.y = quat.y();
  block_pose.orientation.z = quat.z();
  block_pose.orientation.w = quat.w();

  // Block1
  MetaBlock block1 = MetaBlock("Block1", block_pose);
  block_locations.push_back(block1);

  // Block2
  block_pose.position.z = block_pose.position.z + BLOCK_SIZE + BLOCK_SIZE*0.4;  // Stack ontop
  MetaBlock block2 = MetaBlock("Block2", block_pose);
  block_locations.push_back(block2);

  // Block3
  block_pose.position.z = block_pose.position.z + BLOCK_SIZE + BLOCK_SIZE*0.4;  // Stack ontop
  MetaBlock block3 = MetaBlock("Block3", block_pose);
  block_locations.push_back(block3);

  // Block4
  block_pose.position.z = block_pose.position.z + BLOCK_SIZE + BLOCK_SIZE*0.4;  // Stack ontop
  MetaBlock block4 = MetaBlock("Block4", block_pose);
  block_locations.push_back(block3);
}

int main(int argc, char **argv)
{
  ros::init (argc, argv, "clamarm_pick_place");
  ros::AsyncSpinner spinner(1);
  spinner.start();

  ros::NodeHandle nh;
  pub_co_ = nh.advertise<moveit_msgs::CollisionObject>("collision_object", 10);
  pub_aco_ = nh.advertise<moveit_msgs::AttachedCollisionObject>("/attached_collision_object", 10);

  ros::Duration(1.0).sleep();

  // ---------------------------------------------------------------------------------------------
  // Load the Robot Viz Tools for publishing to Rviz
  rviz_tools_.reset(new block_grasp_generator::RobotVizTools( RVIZ_MARKER_TOPIC, EE_GROUP, PLANNING_GROUP_NAME,
                                                              BASE_LINK));

  // ---------------------------------------------------------------------------------------------
  // Load grasp generator
  loadRobotGraspData(); // Load robot specific data
  block_grasp_generator_.reset(new block_grasp_generator::BlockGraspGenerator(rviz_tools_));

  // ---------------------------------------------------------------------------------------------
  // Create MoveGroup
  group_.reset(new move_group_interface::MoveGroup(PLANNING_GROUP_NAME));
  group_->setPlanningTime(30.0);

  ros::Duration(1.0).sleep();

  // --------------------------------------------------------------------------------------------------------
  // Start pick and place loop

  geometry_msgs::Pose start_block_pose;
  geometry_msgs::Pose end_block_pose;

  std::vector<MetaBlock> goal_block_locations;
  getGoalBlocks(goal_block_locations);

  // Remvoed attached objects
  cleanupACO();
  cleanupCO("Block1");
  cleanupCO("Block2");
  cleanupCO("Block3");
  cleanupCO("Block4");

  int goal_id = 0;
  while(true && ros::ok())
  {
    bool foundBlock = false;
    while(!foundBlock && ros::ok())
    {
      generateRandomBlock(start_block_pose);

      publishCollisionBlock(start_block_pose, goal_block_locations[goal_id].first);

      ROS_INFO_STREAM_NAMED("simple_pick_place","Published collision object");

      //MetaBlock start_block = MetaBlock(goal_block_locations[goal_id].first,start_block_pose);

      if( !pick(start_block_pose, goal_block_locations[goal_id].first) )
      {
        ROS_ERROR_STREAM_NAMED("simple_pick_place","Pick failed. Retrying.");
        cleanupCO(goal_block_locations[goal_id].first);
      }
      else
      {
        ROS_INFO_STREAM_NAMED("simple_pick_place","Done with pick");
        foundBlock = true;
      }
    }

    ros::Duration(1.0).sleep();

    bool putBlock = false;
    while(!putBlock && ros::ok())
    {
      //generateRandomBlock(end_block_pose);
      end_block_pose = goal_block_locations[goal_id].second;

      if( !place(goal_block_locations[goal_id]) )
      {
        ROS_ERROR_STREAM_NAMED("simple_pick_place","Place failed. Retrying.");
      }
      else
      {
        ROS_INFO_STREAM_NAMED("simple_pick_place","Done with place");
        putBlock = true;
        ++goal_id;
        if( goal_id > goal_block_locations.size() )
        {
          ROS_WARN_STREAM_NAMED("","Out of goal locations");
          ros::shutdown();
          return 0;
        }
      }
    }

    // Cycle placed block to become pick block
    start_block_pose = end_block_pose;
  }

  ros::shutdown();
  return 0;
}






/*
// remove pole
co.id = "pole";
co.operation = moveit_msgs::CollisionObject::REMOVE;
pub_co_.publish(co);

// add pole
co.operation = moveit_msgs::CollisionObject::ADD;
co.primitives.resize(1);
co.primitives[0].type = shape_msgs::SolidPrimitive::BOX;
co.primitives[0].dimensions.resize(shape_tools::SolidPrimitiveDimCount<shape_msgs::SolidPrimitive::BOX>::value);
co.primitives[0].dimensions[shape_msgs::SolidPrimitive::BOX_X] = 0.3;
co.primitives[0].dimensions[shape_msgs::SolidPrimitive::BOX_Y] = 0.1;
co.primitives[0].dimensions[shape_msgs::SolidPrimitive::BOX_Z] = 1.0;
co.primitive_poses.resize(1);
co.primitive_poses[0].position.x = 0.7;
co.primitive_poses[0].position.y = -0.4;
co.primitive_poses[0].position.z = 0.85;
co.primitive_poses[0].orientation.w = 1.0;
pub_co_.publish(co);
*/


// add path constraints
/*
  moveit_msgs::Constraints constr;
  constr.orientation_constraints.resize(1);
  moveit_msgs::OrientationConstraint &ocm = constr.orientation_constraints[0];
  ocm.link_name = "r_wrist_roll_link";
  ocm.header.frame_id = p.header.frame_id;
  ocm.orientation.x = 0.0;
  ocm.orientation.y = 0.0;
  ocm.orientation.z = 0.0;
  ocm.orientation.w = 1.0;
  ocm.absolute_x_axis_tolerance = 0.2;
  ocm.absolute_y_axis_tolerance = 0.2;
  ocm.absolute_z_axis_tolerance = M_PI;
  ocm.weight = 1.0;
  group.setPathConstraints(constr);
*/

/*
  manipulation_msgs::GripperTranslation gripper_approach;
  gripper_approach.direction.header.frame_id = BASE_LINK;
  gripper_approach.direction.header.stamp = ros::Time::now();
  gripper_approach.direction.vector.z = -1.0;
  gripper_approach.min_distance = 0.025;
  gripper_approach.desired_distance = 0.050;
  ROS_WARN_STREAM_NAMED("","is the same? \n" << gripper_approach);

  ros::shutdown();
  exit(-12);

  // Retreat
  place_loc.retreat.direction.header.frame_id = BASE_LINK;
  place_loc.retreat.direction.header.stamp = ros::Time::now();
  place_loc.retreat.direction.vector.z = 1.0;
  place_loc.retreat.min_distance = 0.025;
  place_loc.retreat.desired_distance = 0.050;
*/
