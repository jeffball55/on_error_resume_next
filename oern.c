#define _GNU_SOURCE 1
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include <ucontext.h>

void segfault_sigaction(int signal, siginfo_t *si, void * ptr)
{
  ((ucontext_t *)ptr)->uc_mcontext.gregs[REG_RIP]++; 
}

static void setup_on_error_resume_next() __attribute__((constructor));
void setup_on_error_resume_next()
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sigaction));
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = segfault_sigaction;
  sa.sa_flags   = SA_SIGINFO;

  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGILL, &sa, NULL);
  sigaction(SIGBUS, &sa, NULL);
}

