#include "../log_boii.h"

int
main()
{
  log_trace("Initializing Video Subsystem ...");
  log_debug("Video Subsystem initialized.");
  log_info("Creating window ...");
  log_debug("Window created.");
  log_info("Creating renderer ...");
  log_warn("Unsupported renderer flags for this platform.");
  log_error("Unable to create renderer: %s", "Unsupported renderer flag.");
  log_fatal("Exiting ..., as renderer was not created.");
  log_trace("Cleaning up resources ...");
  log_info("Done.");
  return 0;
}