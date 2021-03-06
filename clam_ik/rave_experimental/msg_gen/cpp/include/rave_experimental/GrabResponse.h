/* Auto-generated by genmsg_cpp for file /home/shenas/rave_experimental/msg/GrabResponse.msg */
#ifndef RAVE_EXPERIMENTAL_MESSAGE_GRABRESPONSE_H
#define RAVE_EXPERIMENTAL_MESSAGE_GRABRESPONSE_H
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
struct GrabResponse_ : public ros::Message
{
  typedef GrabResponse_<ContainerAllocator> Type;

  GrabResponse_()
  : object_id()
  , errno(0)
  {
  }

  GrabResponse_(const ContainerAllocator& _alloc)
  : object_id(_alloc)
  , errno(0)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _object_id_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  object_id;

  typedef uint32_t _errno_type;
  uint32_t errno;


private:
  static const char* __s_getDataType_() { return "rave_experimental/GrabResponse"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "9e7f17b0f2355c303da59bb9ccc1d435"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "string object_id\n\
uint32 errno\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, object_id);
    ros::serialization::serialize(stream, errno);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, object_id);
    ros::serialization::deserialize(stream, errno);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(object_id);
    size += ros::serialization::serializationLength(errno);
    return size;
  }

  typedef boost::shared_ptr< ::rave_experimental::GrabResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rave_experimental::GrabResponse_<ContainerAllocator>  const> ConstPtr;
}; // struct GrabResponse
typedef  ::rave_experimental::GrabResponse_<std::allocator<void> > GrabResponse;

typedef boost::shared_ptr< ::rave_experimental::GrabResponse> GrabResponsePtr;
typedef boost::shared_ptr< ::rave_experimental::GrabResponse const> GrabResponseConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::rave_experimental::GrabResponse_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::rave_experimental::GrabResponse_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace rave_experimental

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator>
struct MD5Sum< ::rave_experimental::GrabResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "9e7f17b0f2355c303da59bb9ccc1d435";
  }

  static const char* value(const  ::rave_experimental::GrabResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x9e7f17b0f2355c30ULL;
  static const uint64_t static_value2 = 0x3da59bb9ccc1d435ULL;
};

template<class ContainerAllocator>
struct DataType< ::rave_experimental::GrabResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "rave_experimental/GrabResponse";
  }

  static const char* value(const  ::rave_experimental::GrabResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::rave_experimental::GrabResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string object_id\n\
uint32 errno\n\
\n\
";
  }

  static const char* value(const  ::rave_experimental::GrabResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::rave_experimental::GrabResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.object_id);
    stream.next(m.errno);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct GrabResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rave_experimental::GrabResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::rave_experimental::GrabResponse_<ContainerAllocator> & v) 
  {
    s << indent << "object_id: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.object_id);
    s << indent << "errno: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.errno);
  }
};


} // namespace message_operations
} // namespace ros

#endif // RAVE_EXPERIMENTAL_MESSAGE_GRABRESPONSE_H

