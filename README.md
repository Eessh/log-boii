# Log Boii
A simple header only logging library for C/C++ projects.

## Building
```bash
> gcc log_boii.c tests/test.c -o bin/test
> ./bin/test
[18:25:46] TRACE main:./tests/test.c:5: Initializing Video Subsystem ...
[18:25:46] DEBUG main:./tests/test.c:6: Video Subsystem initialized.
[18:25:46] INFO  main:./tests/test.c:7: Creating window ...
[18:25:46] DEBUG main:./tests/test.c:8: Window created.
[18:25:46] INFO  main:./tests/test.c:9: Creating renderer ...
[18:25:46] WARN  main:./tests/test.c:10: Unsupported renderer flags for this platform.
[18:25:46] ERROR main:./tests/test.c:11: Unable to create renderer: Unsupported renderer flag.
[18:25:46] FATAL main:./tests/test.c:12: Exiting ..., as renderer was not created.
[18:25:46] TRACE main:./tests/test.c:13: Cleaning up resources ...
[18:25:46] INFO  main:./tests/test.c:14: Done.
```
### Colored Output
Define `LOG_BOII__COLORED_LOGS`
```bash
> gcc -DLOG_BOII__COLORED_LOGS log_boii.c tests/test.c -o bin/test
```

### Colored Highlighted Output for `WARN`, `ERROR`, `FATAL` logs
Define `LOG_BOII__HIGHLIGHT_WARN_ERROR_FATAL_STRINGS` for printing whole log string in respective level's color.
```bash
> gcc -DLOG_BOII__COLORED_LOGS -DLOG_BOII__HIGHLIGHT_WARN_ERROR_FATAL_STRINGS log_boii.c tests/test.c -o bin/test
```


## Usage of Log levels
#### FATAL
The `LOG_FATAL` log level annotates messages with the greatest severity. It usually means that something critical is broken, and the application cannot continue to do any more useful work without the intervention of an engineer. Typically, such entries are logged before the application is shut down (with exit code 1) to prevent further data corruption.

Examples of situations that may be logged as FATAL errors include the following:
- Crucial configuration information is missing without fallback defaults.
- Unable to connect to a service crucial to the application's primary function (such as the database).
- Running out of disk space on the server.

#### ERROR
The `LOG_ERROR` log level is used to represent error conditions in an application that prevent a specific operation from running, but the application itself can continue working even if it is at a reduced level of functionality or performance. Generally, ERROR logs should be investigated as soon as possible but they don't carry the same urgency as FATAL messages since the application can continue working.

The occurrence of an error condition in the application does not necessarily mean that it should be logged at the ERROR level. For example, if an exception is expected behavior and does not indicate degradation in application functionality or performance, it can be logged as INFO. Also, errors with a possibility of recovery (such as network connectivity errors) can be labeled as INFO if an automatic recovery strategy is in place (e.g retries). Such conditions can be promoted to the ERROR level if recovery isn't possible after a predetermined time.

Examples of situations that are typically logged at the ERROR level include the following:
- A persistent connection failure to some external resource (after automated recovery attempts have failed).
- Failure to create or update a resource in the system.
- An unexpected error (e.g failed to decode a JSON object).

#### WARN
Messages logged at the `LOG_WARN` level typically indicate that something unexpected happened, but the application can recover and continue to function normally. It is mainly used to draw attention to situations that should be addressed soon before they pose a problem for the application.

Events that may be logged at the WARN level include the following:
- The disk usage on the server is above a configured threshold.
- Memory usage is above a configured threshold.
- The application is taking longer than usual to complete some important tasks (degraded performance).

#### INFO
`LOG_INFO` level messages indicate events in the system that are significant to the business purpose of the application. Such events are logged to show that the system is operating normally. For example, a service was started or stopped, some resource was created, accessed, updated, or deleted in the database, and so on. Production systems typically default to logging at this level so that a summary of the application's normal behavior is visible to anyone reading the logs.

Other events that are typically logged at the INFO level include the following:
- The state of an operation has changed (e.g from "PENDING" to "IN PROGRESS").
- The application is listening on a specific port.
- A scheduled job was completed successfully.

#### DEBUG
The `LOG_DEBUG` level is used for logging messages that help developers find out what went wrong during a debugging session. While the specifics of what messages to log at the DEBUG level is dependent on your application, you generally want to include detailed information that can help developers troubleshoot an issue quickly. This can include variable state in the surrounding scope, or relevant error codes. Unlike TRACE (below), DEBUG level logging can be turned on in production without making the application unusable, but it should not be left on indefinitely to ensure optimal performance of the system.

#### TRACE
The `LOG_TRACE` level is used for tracing the path of code execution in a program. For example, you may use it to trace the processing of a incoming request or an algorithm's steps to solve a problem. Generally, TRACE is used for showing the flow of the program, and to provide a detailed breakdown of the sequence of events that led to a crash, a silent failure, an error, or some other event logged at a different level.

Concrete examples of messages that should be logged at the TRACE level include the following:
- Entered or exited a function or method, perhaps with the processing duration.
- Calculation x + y produced output z.
- Starting or ending an operation and any intermediate state changes.

As you can see, the information logged at this level generally tries to capture every possible detail about the program's execution. Therefore, TRACE logging should only be enabled for short periods due to the significant performance degradation that it often causes. You will typically enable it only in development and testing environments.


## Controlling your application's log volume
Log levels are the primary way to control your application's volume of log entries. Once you select your default level, all log entries that are labeled with a severity lower than the default will not be recorded. For example, logging at the WARN level will cause INFO, DEBUG and TRACE messages to be ignored.

As you go down in default severity, the number of entries that are produced will increase, so it's a good idea to turn on only what is necessary to avoid being flooded with too much information. A typical default for production environments is INFO, which records messages logged at the INFO level or higher priority (WARN, ERROR and FATAL). You can change this to WARN if you only want to record events that indicate problems or potential problems.

When troubleshooting a problem in production, you might want to reduce the default severity of recorded messages to DEBUG. This level will typically produce a voluminous output filled with enough context that will help developers debug the issue, but it should be turned off afterward to prevent flooding the system with irrelevant log entries during normal operation of the application.

The TRACE level produces even more logs than DEBUG so it shouldn't be used in production for sustained periods. It's better utilized in a development or testing environment where system performance degradation isn't a critical consideration.
