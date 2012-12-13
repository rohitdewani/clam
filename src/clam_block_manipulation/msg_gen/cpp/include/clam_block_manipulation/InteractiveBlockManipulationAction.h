/* Auto-generated by genmsg_cpp for file /home/dave/ros/clam/clam_block_manipulation/msg/InteractiveBlockManipulationAction.msg */
#ifndef CLAM_BLOCK_MANIPULATION_MESSAGE_INTERACTIVEBLOCKMANIPULATIONACTION_H
#define CLAM_BLOCK_MANIPULATION_MESSAGE_INTERACTIVEBLOCKMANIPULATIONACTION_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "clam_block_manipulation/InteractiveBlockManipulationActionGoal.h"
#include "clam_block_manipulation/InteractiveBlockManipulationActionResult.h"
#include "clam_block_manipulation/InteractiveBlockManipulationActionFeedback.h"

namespace clam_block_manipulation
{
template <class ContainerAllocator>
struct InteractiveBlockManipulationAction_ {
  typedef InteractiveBlockManipulationAction_<ContainerAllocator> Type;

  InteractiveBlockManipulationAction_()
  : action_goal()
  , action_result()
  , action_feedback()
  {
  }

  InteractiveBlockManipulationAction_(const ContainerAllocator& _alloc)
  : action_goal(_alloc)
  , action_result(_alloc)
  , action_feedback(_alloc)
  {
  }

  typedef  ::clam_block_manipulation::InteractiveBlockManipulationActionGoal_<ContainerAllocator>  _action_goal_type;
   ::clam_block_manipulation::InteractiveBlockManipulationActionGoal_<ContainerAllocator>  action_goal;

  typedef  ::clam_block_manipulation::InteractiveBlockManipulationActionResult_<ContainerAllocator>  _action_result_type;
   ::clam_block_manipulation::InteractiveBlockManipulationActionResult_<ContainerAllocator>  action_result;

  typedef  ::clam_block_manipulation::InteractiveBlockManipulationActionFeedback_<ContainerAllocator>  _action_feedback_type;
   ::clam_block_manipulation::InteractiveBlockManipulationActionFeedback_<ContainerAllocator>  action_feedback;


  typedef boost::shared_ptr< ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct InteractiveBlockManipulationAction
typedef  ::clam_block_manipulation::InteractiveBlockManipulationAction_<std::allocator<void> > InteractiveBlockManipulationAction;

typedef boost::shared_ptr< ::clam_block_manipulation::InteractiveBlockManipulationAction> InteractiveBlockManipulationActionPtr;
typedef boost::shared_ptr< ::clam_block_manipulation::InteractiveBlockManipulationAction const> InteractiveBlockManipulationActionConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace clam_block_manipulation

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> > {
  static const char* value() 
  {
    return "6b355c8305ef3300641af877554e1717";
  }

  static const char* value(const  ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x6b355c8305ef3300ULL;
  static const uint64_t static_value2 = 0x641af877554e1717ULL;
};

template<class ContainerAllocator>
struct DataType< ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> > {
  static const char* value() 
  {
    return "clam_block_manipulation/InteractiveBlockManipulationAction";
  }

  static const char* value(const  ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
InteractiveBlockManipulationActionGoal action_goal\n\
InteractiveBlockManipulationActionResult action_result\n\
InteractiveBlockManipulationActionFeedback action_feedback\n\
\n\
================================================================================\n\
MSG: clam_block_manipulation/InteractiveBlockManipulationActionGoal\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalID goal_id\n\
InteractiveBlockManipulationGoal goal\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: actionlib_msgs/GoalID\n\
# The stamp should store the time at which this goal was requested.\n\
# It is used by an action server when it tries to preempt all\n\
# goals that were requested before a certain time\n\
time stamp\n\
\n\
# The id provides a way to associate feedback and\n\
# result message with specific goal requests. The id\n\
# specified must be unique.\n\
string id\n\
\n\
\n\
================================================================================\n\
MSG: clam_block_manipulation/InteractiveBlockManipulationGoal\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#goal definition\n\
string frame\n\
float32 block_size\n\
\n\
================================================================================\n\
MSG: clam_block_manipulation/InteractiveBlockManipulationActionResult\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalStatus status\n\
InteractiveBlockManipulationResult result\n\
\n\
================================================================================\n\
MSG: actionlib_msgs/GoalStatus\n\
GoalID goal_id\n\
uint8 status\n\
uint8 PENDING         = 0   # The goal has yet to be processed by the action server\n\
uint8 ACTIVE          = 1   # The goal is currently being processed by the action server\n\
uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing\n\
                            #   and has since completed its execution (Terminal State)\n\
uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)\n\
uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due\n\
                            #    to some failure (Terminal State)\n\
uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,\n\
                            #    because the goal was unattainable or invalid (Terminal State)\n\
uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing\n\
                            #    and has not yet completed execution\n\
uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,\n\
                            #    but the action server has not yet confirmed that the goal is canceled\n\
uint8 RECALLED        = 8   # The goal received a cancel request before it started executing\n\
                            #    and was successfully cancelled (Terminal State)\n\
uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be\n\
                            #    sent over the wire by an action server\n\
\n\
#Allow for the user to associate a string with GoalStatus for debugging\n\
string text\n\
\n\
\n\
================================================================================\n\
MSG: clam_block_manipulation/InteractiveBlockManipulationResult\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#result definition\n\
geometry_msgs/Pose pickup_pose\n\
geometry_msgs/Pose place_pose\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of postion and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
================================================================================\n\
MSG: clam_block_manipulation/InteractiveBlockManipulationActionFeedback\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalStatus status\n\
InteractiveBlockManipulationFeedback feedback\n\
\n\
================================================================================\n\
MSG: clam_block_manipulation/InteractiveBlockManipulationFeedback\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#feedback\n\
\n\
\n\
";
  }

  static const char* value(const  ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.action_goal);
    stream.next(m.action_result);
    stream.next(m.action_feedback);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct InteractiveBlockManipulationAction_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::clam_block_manipulation::InteractiveBlockManipulationAction_<ContainerAllocator> & v) 
  {
    s << indent << "action_goal: ";
s << std::endl;
    Printer< ::clam_block_manipulation::InteractiveBlockManipulationActionGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.action_goal);
    s << indent << "action_result: ";
s << std::endl;
    Printer< ::clam_block_manipulation::InteractiveBlockManipulationActionResult_<ContainerAllocator> >::stream(s, indent + "  ", v.action_result);
    s << indent << "action_feedback: ";
s << std::endl;
    Printer< ::clam_block_manipulation::InteractiveBlockManipulationActionFeedback_<ContainerAllocator> >::stream(s, indent + "  ", v.action_feedback);
  }
};


} // namespace message_operations
} // namespace ros

#endif // CLAM_BLOCK_MANIPULATION_MESSAGE_INTERACTIVEBLOCKMANIPULATIONACTION_H

