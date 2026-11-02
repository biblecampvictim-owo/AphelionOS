#pragma once
#define FLAG_SET(x, flag) x |= flag
#define FLAG_UNSET(x, flag) x &= -(flag)

//is this even being used anywhere?? I can't remember.