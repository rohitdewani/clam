/* Auto-generated by genmsg_cpp for file /home/shenas/rave_experimental/msg/GrabCommand.msg */
#ifndef RAVE_EXPERIMENTAL_MESSAGE_GRABCOMMAND_H
#define RAVE_EXPERIMENTAL_MESSAGE_GRABCOMMAND_H
#include <string>
#include <vector>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/message.h"
#include "ros/time.h"


namespace rave_experimental
{
template <class ContainerAllocator>
struct GrabCommand_ : public ros::Message
{
  typedef GrabCommand_<ContainerAllocator> Type;

  GrabCommand_()
  : object_id()
  , use_visual_feedback(false)
  {
  }

  GrabCommand_(const ContainerAllocator& _alloc)
  : object_id(_alloc)
  , use_visual_feedback(false)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _object_id_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  object_id;

  typedef uint8_t _use_visual_feedback_type;
  uint8_t use_visual_feedback;


private:
  static const char* __s_getDataType_() { return "rave_experimental/GrabCommand"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "5da422b82edbbff9f2e278bcc00f2eb3"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "string object_id\n\
bool use_visual_feedback\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, object_id);
    ros::serialization::serialize(stream, use_visual_feedback);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, object_id);
    ros::serialization::deserialize(stream, use_visual_feedback);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(object_id);
    size += ros::serialization::serializationLength(use_visual_feedback);
    return size;
  }

  typedef boost::shared_ptr< ::rave_experimental::GrabCommand_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rave_experimental::GrabCommand_<ContainerAllocator>  const> ConstPtr;
}; // struct GrabCommand
typedef  ::rave_experimental::GrabCommand_<std::allocator<void> > GrabCommand;

typedef boost::shared_ptr< ::rave_experimental::GrabCommand> GrabCommandPtr;
typedef boost::shared_ptr< ::rave_experimental::GrabCommand const> GrabCommandConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::rave_experimental::GrabCommand_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::rave_experimental::GrabCommand_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace rave_experimental

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator>
struct MD5Sum< ::rave_experimental::GrabCommand_<ContainerAllocator> > {
  static const char* value() 
  {
    return "5da422b82edbbff9f2e278bcc00f2eb3";
  }

  static const char* value(const  ::rave_experimental::GrabCommand_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x5da422b82edbbff9ULL;
  static const uint64_t static_value2 = 0xf2e278bcc00f2eb3ULL;
};

template<class ContainerAllocator>
struct DataType< ::rave_experimental::GrabCommand_<ContainerAllocator> > {
  static const char* value() 
  {
    return "rave_experimental/GrabCommand";
  }

  static const char* value(const  ::rave_experimental::GrabCommand_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::rave_experimental::GrabCommand_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string object_id\n\
bool use_visual_feedback\n\
\n\
";
  }

  static const char* value(const  ::rave_experimental::GrabCommand_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::rave_experimental::GrabCommand_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.object_id);
    stream.next(m.use_visual_feedback);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct GrabCommand_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rave_experimental::GrabCommand_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::rave_experimental::GrabCommand_<ContainerAllocator> & v) 
  {
    s << indent << "object_id: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.object_id);
    s << indent << "use_visual_feedback: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.use_visual_feedback);
  }
};


} // namespace message_operations
} // namespace ros

#endif // RAVE_EXPERIMENTAL_MESSAGE_GRABCOMMAND_H

