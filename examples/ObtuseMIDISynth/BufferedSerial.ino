
// yet another circular buffer, read/write arrays (as circle_buf.h) and overwrite (as the others). Fixed type (unlike all).
// warning: most probably non thread-safe, and even interrupt-safe -- worst-case messages will be temporarily mixed-up, no memory corruption it seems (finger crossed)

// buffer for storing data
char buffchar[128];
size_t buffWpos = 0;
size_t buffRpos = 0;

// how many was written since last fetch
size_t nbWritten = 0;

// send message to buffer
// discard all values if not enough

size_t SprintCapacity() {
  return (sizeof(buffchar));
}
// how much is stored in the buffer
size_t SprintAvailable() {
  return (max(0, (int)SprintCapacity() - (int)nbWritten));
}

// reset buffer (only heads position, not the actual data)
void SprintClear() {
  buffWpos = 0;
  buffRpos = 0;
  nbWritten = 0;
}

void Sprint(const char* msg) {
  // how much to copy
  size_t len = strlen(msg);
  // don't deal with empty
  if (len == 0) {
    return;
  }

  // where to start copying in the message
  size_t msg_pos = 0;
  // if the string is too big, only take care of what fits in memory
  if (len >= SprintCapacity()) {
    msg_pos = len - SprintCapacity();
    len =  SprintCapacity();
    buffWpos = 0;
    buffRpos = 0;
  }
  // will not fill the whole buffer but still erasing data, update read position in advance
  else if (len > SprintAvailable()) {
    buffRpos = (buffRpos + len - SprintAvailable()) %  SprintCapacity();
  }
  // copy first part of message
  size_t nbTowrite = 0;
  while (len > 0) {
    // write to remaining space until all is done
    nbTowrite = min(len, SprintCapacity() - buffWpos);
    memcpy(buffchar + buffWpos, msg + msg_pos, nbTowrite);
    // do not actually check written byte so as not to block if something goes wrong
    len = len - nbTowrite;
    nbWritten = nbWritten + nbTowrite;
    buffWpos = (buffWpos + nbTowrite) % SprintCapacity();
    msg_pos = msg_pos + nbTowrite;
  }
}

void Sprintln(const char* msg) {
  Sprint(msg);
  Sprint("\n");
}

void Sprint(byte val) {
  Sprint(String(val).c_str());
}

void Sprintln(byte val) {
  Sprint(val);
  Sprint("\n");
}

void Sprint(float val) {
  Sprint(String(val).c_str());
}

void Sprintln(float val) {
  Sprint(val);
  Sprint("\n");
}

void Sprint(double val) {
  Sprint(String(val).c_str());
}

void Sprintln(double val) {
  Sprint(val);
  Sprint("\n");
}

void Sprint(int val) {
  Sprint(String(val).c_str());
}

void Sprintln(int val) {
  Sprint(val);
  Sprint("\n");
}


void Sprint(unsigned int val) {
  Sprint(String(val).c_str());
}

void Sprintln(unsigned int val) {
  Sprint(val);
  Sprint("\n");
}

void Sprint(long int val) {
  Sprint(String(val).c_str());
}

void Sprintln(long int val) {
  Sprint(val);
  Sprint("\n");
}

void Sprint(long unsigned int val) {
  Sprint(String(val).c_str());
}

void Sprintln(long unsigned int val) {
  Sprint(val);
  Sprint("\n");
}

// fetch messages and print to Serial. Prepend with info about number of missing data if any
void Sfetch() {
  // temporary buffer to fetch data (last pos for *mandatory* \0)
  static char buff[64];
  // will not try to fetch more than what could possibly be written
  size_t toFetch = nbWritten;
  if (toFetch > SprintCapacity()) {
    toFetch = SprintCapacity();
  }
  if (nbWritten > toFetch) {
    Serial.print("[... skipped ");
    Serial.print(nbWritten - toFetch);
    Serial.print(" chars...]");
  }

  // how many bytes to copy per loop between (considering we might loop data buffer)
  size_t nbToCopy = 0;
  // how many bytes to temp buffer
  size_t nbCopied = 0;
  while (toFetch > 0) {
    // not coping beyond both buffers, and more than needed
    nbToCopy = min(toFetch, min(sizeof(buff) - nbCopied - 1, SprintCapacity() - buffRpos));
    memcpy(buff + nbCopied, buffchar + buffRpos, nbToCopy);
    toFetch = toFetch - nbToCopy;
    buffRpos = (buffRpos + nbToCopy) % SprintCapacity();
    nbCopied = nbCopied + nbToCopy;
    // one buffer ready to be sent
    if (nbCopied >= sizeof(buff) - 1) {
      buff[sizeof(buff) - 1] = '\0';
      Serial.print(buff);
      nbCopied = 0;
    }
  }

  // remnent data in buffer, set end pos with \0
  if (nbCopied > 0) {
    buff[nbCopied] = '\0';
    Serial.print(buff);
  }

  // discard everything and start anew -- especially interesting if racing condition messed-up the inner stae
  SprintClear();
}
