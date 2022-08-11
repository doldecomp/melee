#include <MSL/wchar_io.h>

int fwide(FILE* stream, int mode)
{
	int orientation;
	int result;
	
	if (stream->mode.file_kind == __closed_file)
		return 0;
	orientation = stream->mode.file_orientation;
	switch (orientation)
	{
		case __unoriented:
			if (mode > 0)
				stream->mode.file_orientation = __wide_oriented;
			else if (mode < 0)
				stream->mode.file_orientation = __char_oriented;
			result = mode;
			break;
			
		case __wide_oriented:
			result = 1;
			break;
			
		case __char_oriented:
			result = -1;
			break;
	}
	return result;
}
