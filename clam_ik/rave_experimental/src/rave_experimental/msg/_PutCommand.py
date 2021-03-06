"""autogenerated by genmsg_py from PutCommand.msg. Do not edit."""
import roslib.message
import struct


class PutCommand(roslib.message.Message):
  _md5sum = "f555af83d35595cf42f4aeb704d9cd78"
  _type = "rave_experimental/PutCommand"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """string object_id
float32 x_offset
float32 y_offset
float32 z_offset
float32 roll
float32 pitch
float32 yaw
bool release

"""
  __slots__ = ['object_id','x_offset','y_offset','z_offset','roll','pitch','yaw','release']
  _slot_types = ['string','float32','float32','float32','float32','float32','float32','bool']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       object_id,x_offset,y_offset,z_offset,roll,pitch,yaw,release
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(PutCommand, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.object_id is None:
        self.object_id = ''
      if self.x_offset is None:
        self.x_offset = 0.
      if self.y_offset is None:
        self.y_offset = 0.
      if self.z_offset is None:
        self.z_offset = 0.
      if self.roll is None:
        self.roll = 0.
      if self.pitch is None:
        self.pitch = 0.
      if self.yaw is None:
        self.yaw = 0.
      if self.release is None:
        self.release = False
    else:
      self.object_id = ''
      self.x_offset = 0.
      self.y_offset = 0.
      self.z_offset = 0.
      self.roll = 0.
      self.pitch = 0.
      self.yaw = 0.
      self.release = False

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    @param buff: buffer
    @type  buff: StringIO
    """
    try:
      _x = self.object_id
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_6fB.pack(_x.x_offset, _x.y_offset, _x.z_offset, _x.roll, _x.pitch, _x.yaw, _x.release))
    except struct.error, se: self._check_types(se)
    except TypeError, te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    @param str: byte array of serialized message
    @type  str: str
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.object_id = str[start:end]
      _x = self
      start = end
      end += 25
      (_x.x_offset, _x.y_offset, _x.z_offset, _x.roll, _x.pitch, _x.yaw, _x.release,) = _struct_6fB.unpack(str[start:end])
      self.release = bool(self.release)
      return self
    except struct.error, e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    @param buff: buffer
    @type  buff: StringIO
    @param numpy: numpy python module
    @type  numpy module
    """
    try:
      _x = self.object_id
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_6fB.pack(_x.x_offset, _x.y_offset, _x.z_offset, _x.roll, _x.pitch, _x.yaw, _x.release))
    except struct.error, se: self._check_types(se)
    except TypeError, te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    @param str: byte array of serialized message
    @type  str: str
    @param numpy: numpy python module
    @type  numpy: module
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.object_id = str[start:end]
      _x = self
      start = end
      end += 25
      (_x.x_offset, _x.y_offset, _x.z_offset, _x.roll, _x.pitch, _x.yaw, _x.release,) = _struct_6fB.unpack(str[start:end])
      self.release = bool(self.release)
      return self
    except struct.error, e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
_struct_6fB = struct.Struct("<6fB")
