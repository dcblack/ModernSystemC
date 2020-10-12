About the Report utilities
==========================

The report utilities are intended to simplify SystemC reporting and
provide more flexibility, while keeping the implementation lightweight.

Foremost are the streaming macros that all steaming syntax to be combined
with `SC_REPORT_*` macros.

Syntax
------

- `ASSERT(expression, message_stream)`
- `REPORT(message_type, message_stream);`
- `INFO(verbosity_level, message_stream);`
- `DEBUG(message_stream);`
- `MESSAGE(message_stream);`
- `MEND(verbosity_level);`
- `RULER(char);`
- `TODO(message_stream);`
- `NOT_YET_IMPLEMENTED();`

Message types are: FATAL, ERROR, WARNING, and INFO

Verbosity levels are: ALWAYS, LOW, MEDIUM, HIGH, DEBUG

The MESSAGE macro doesn't output anything, but rather builds up
a message to be emitted by REPORT, INFO or MEND.

Assumes you define in every implementation file (i.e. .cpp):

```cpp
#include "report/report.hpp"
namespace {
  char const * const MSGID{ "/Company/Group/Project/Module" };
}
```

For header files leave off the name space and put in the function
or define a `static constexpr char const * const` class member. Must not allow to escape
the header. So a #define is inappropriate. Here is an example:

```cpp
class Xyz {
 ...
private:
 static char const * const MSGID { "/Company/Group/Project/Module" };
};
```

Note that the DEBUG macro has an additional qualification. It checks command-line arguments
for an option to enable the debug message. Using `-debugall` unconditionally enables all
debug statements. Using `-debug=INSTANCE` allows you to enable it only when the current instance
matches the specified instance. This argument may be repeated.

Usage Example
-------------

```cpp
#include "report/report.hpp"
namespace { char const * const MSGID{ "/Doulos/Example/Report" }; }
void thread() {
  ASSERT( n > -2, "Value of n may only be positive or -1. Currently " << n );
  REPORT( ERROR, "Data " << data << " doesn't match expected " << expected );
  INFO( HIGH, "Packet contains " << packet );
  DEBUG( "Suspect contains " << packet );
  TODO( "Fix report handler to remove blank line after REPORT_INFO" );
  NOT_YET_IMPLEMENTED();
  MESSAGE( "Map contents:\n" );
  for( const auto& v : my_map ) {
   MESSAGE( "  " << v.first << ": " << v.second << "\n" );
  }
  MEND( HIGH ); // or REPORT( WARNING, "" );
}
```

### The end
<!-- vim:tw=78
-->
