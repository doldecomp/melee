class InputStream():
    """Input file stream with configurable endianness (byteorder)."""
    endian: int
    pos: int
    _size: int
    data: bytes

    # Endianness
    ENDIAN_LITTLE = 0
    ENDIAN_BIG = 1
    ENDIAN_MAX = 2

    # Seek type
    SEEK_BEGIN = 0
    SEEK_CURRENT = 1
    SEEK_END = 2
    SEEK_MAX = 3

    def __init__(self, _data: bytes, _endian: int):
        """Constructor
            _data (bytes): File data
            _endian (int): Target endianness (Endianness.LITTLE / Endianness.BIG)
        """
        assert _endian >= InputStream.ENDIAN_LITTLE and _endian < InputStream.ENDIAN_MAX
        self.endian = _endian
        self.pos = 0
        self._size = len(_data)
        self.data = _data

    @staticmethod
    def open_file(path: str, _endian: int) -> "InputStream":
        """Construct an input stream for the file at the specified path,
        using the specified endianness."""
        with open(path, "rb") as f:
            return InputStream(f.read(), _endian)

    def eof(self) -> bool:
        """Check if the stream has hit the end of the file."""
        return self.pos >= len(self.data)

    def read(self, size: int) -> bytearray:
        """Read bytes from the stream."""
        assert self.pos + size <= len(self.data)
        data = self.data[self.pos: self.pos + size]
        self.pos += size
        return data

    def seek(self, ofs: int, whence: int):
        """Seek the stream position."""
        if whence == InputStream.SEEK_BEGIN:
            self.pos = ofs
        elif whence == InputStream.SEEK_CURRENT:
            self.pos = self.pos + ofs
        elif whence == InputStream.SEEK_END:
            self.pos = self._size - ofs
        else:
            assert False, "Invalid seek whence"
        # Clamp position to before EOF
        self.pos = min(self.pos, self._size - 1)

    def get_s8(self) -> int:
        """Read a signed 8-bit integer from the stream."""
        return self._from_bytes(self.read(1), True)

    def get_u8(self) -> int:
        """Read an unsigned 8-bit integer from the stream."""
        return self._from_bytes(self.read(1), False)

    def get_s16(self) -> int:
        """Read a signed 16-bit integer from the stream."""
        return self._from_bytes(self.read(2), True)

    def get_u16(self) -> int:
        """Read an unsigned 16-bit integer from the stream."""
        return self._from_bytes(self.read(2), False)

    def get_s32(self) -> int:
        """Read a signed 32-bit integer from the stream."""
        return self._from_bytes(self.read(4), True)

    def get_u32(self) -> int:
        """Read an unsigned 32-bit integer from the stream."""
        return self._from_bytes(self.read(4), False)

    def get_string(self) -> str:
        """Read a string from the stream."""
        string = ""
        c = self.get_int8()
        while c != 0x00:
            string += chr(c)
            c = self.get_int8()

    def _from_bytes(self, data: bytes, signed: bool) -> int:
        """Convert bytes from the stream into an integer"""
        endian_str = ("little", "big")[self.endian]
        return int.from_bytes(data, byteorder=endian_str, signed=bool)
