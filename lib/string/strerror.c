#include <string.h>
#include <errno.h>

const char *strerror(int errnum)
{
	const char *ret = NULL;
	switch (errnum) {
		case E2BIG:
			ret = "Argument list too long.";
			break;
		case EACCES:
			ret = "Permission denied.";
			break;
		case EADDRINUSE:
			ret = "Address in use.";
			break;
		case EADDRNOTAVAIL:
			ret = "Address not available.";
			break;
		case EAFNOSUPPORT:
			ret = "Address family not supported.";
			break;
		case EAGAIN:
			ret = "Resource unavailable, try again (may be the same value as case EWOULDBLOCK]).";
			break;
		case EALREADY:
			ret = "Connection already in progress.";
			break;
		case EBADF:
			ret = "Bad file descriptor.";
			break;
		case EBADMSG:
			ret = "Bad message.";
			break;
		case EBUSY:
			ret = "Device or resource busy.";
			break;
		case ECANCELED:
			ret = "Operation canceled.";
			break;
		case ECHILD:
			ret = "No child processes.";
			break;
		case ECONNABORTED:
			ret = "Connection aborted.";
			break;
		case ECONNREFUSED:
			ret = "Connection refused.";
			break;
		case ECONNRESET:
			ret = "Connection reset.";
			break;
		case EDEADLK:
			ret = "Resource deadlock would occur.";
			break;
		case EDESTADDRREQ:
			ret = "Destination address required.";
			break;
		case EDOM:
			ret = "Mathematics argument out of domain of function.";
			break;
		case EDQUOT:
			ret = "Reserved.";
			break;
		case EEXIST:
			ret = "File exists.";
			break;
		case EFAULT:
			ret = "Bad address.";
			break;
		case EFBIG:
			ret = "File too large.";
			break;
		case EHOSTUNREACH:
			ret = "Host is unreachable.";
			break;
		case EIDRM:
			ret = "Identifier removed.";
			break;
		case EILSEQ:
			ret = "Illegal byte sequence.";
			break;
		case EINPROGRESS:
			ret = "Operation in progress.";
			break;
		case EINTR:
			ret = "Interrupted function.";
			break;
		case EINVAL:
			ret = "Invalid argument.";
			break;
		case EIO:
			ret = "I/O error.";
			break;
		case EISCONN:
			ret = "Socket is connected.";
			break;
		case EISDIR:
			ret = "Is a directory.";
			break;
		case ELOOP:
			ret = "Too many levels of symbolic links.";
			break;
		case EMFILE:
			ret = "Too many open files.";
			break;
		case EMLINK:
			ret = "Too many links.";
			break;
		case EMSGSIZE:
			ret = "Message too large.";
			break;
		case EMULTIHOP:
			ret = "Reserved.";
			break;
		case ENAMETOOLONG:
			ret = "Filename too long.";
			break;
		case ENETDOWN:
			ret = "Network is down.";
			break;
		case ENETRESET:
			ret = "Connection aborted by network.";
			break;
		case ENETUNREACH:
			ret = "Network unreachable.";
			break;
		case ENFILE:
			ret = "Too many files open in system.";
			break;
		case ENOBUFS:
			ret = "No buffer space available.";
			break;
		case ENODATA:
			ret = "case XSR] case Option Start] No message is available on the STREAM head read queue. case Option End]";
			break;
		case ENODEV:
			ret = "No such device.";
			break;
		case ENOENT:
			ret = "No such file or directory.";
			break;
		case ENOEXEC:
			ret = "Executable file format error.";
			break;
		case ENOLCK:
			ret = "No locks available.";
			break;
		case ENOLINK:
			ret = "Reserved.";
			break;
		case ENOMEM:
			ret = "Not enough space.";
			break;
		case ENOMSG:
			ret = "No message of the desired type.";
			break;
		case ENOPROTOOPT:
			ret = "Protocol not available.";
			break;
		case ENOSPC:
			ret = "No space left on device.";
			break;
		case ENOSR:
			ret = "case XSR] case Option Start] No STREAM resources. case Option End]";
			break;
		case ENOSTR:
			ret = "case XSR] case Option Start] Not a STREAM. case Option End]";
			break;
		case ENOSYS:
			ret = "Function not supported.";
			break;
		case ENOTCONN:
			ret = "The socket is not connected.";
			break;
		case ENOTDIR:
			ret = "Not a directory.";
			break;
		case ENOTEMPTY:
			ret = "Directory not empty.";
			break;
		case ENOTSOCK:
			ret = "Not a socket.";
			break;
		case ENOTSUP:
			ret = "Not supported.";
			break;
		case ENOTTY:
			ret = "Inappropriate I/O control operation.";
			break;
		case ENXIO:
			ret = "No such device or address.";
			break;
		case EOPNOTSUPP:
			ret = "Operation not supported on socket.";
			break;
		case EOVERFLOW:
			ret = "Value too large to be stored in data type.";
			break;
		case EPERM:
			ret = "Operation not permitted.";
			break;
		case EPIPE:
			ret = "Broken pipe.";
			break;
		case EPROTO:
			ret = "Protocol error.";
			break;
		case EPROTONOSUPPORT:
			ret = "Protocol not supported.";
			break;
		case EPROTOTYPE:
			ret = "Protocol wrong type for socket.";
			break;
		case ERANGE:
			ret = "Result too large.";
			break;
		case EROFS:
			ret = "Read-only file system.";
			break;
		case ESPIPE:
			ret = "Invalid seek.";
			break;
		case ESRCH:
			ret = "No such process.";
			break;
		case ESTALE:
			ret = "Reserved.";
			break;
		case ETIME:
			ret = "case XSR] case Option Start] Stream ioctl() timeout. case Option End]";
			break;
		case ETIMEDOUT:
			ret = "Connection timed out.";
			break;
		case ETXTBSY:
			ret = "Text file busy.";
			break;
		case EWOULDBLOCK:
			ret = "Operation would block (may be the same value as case EAGAIN]).";
			break;
		case EXDEV:
			ret = "Cross-device link. ";
			break;
	}
	return ret;
}
