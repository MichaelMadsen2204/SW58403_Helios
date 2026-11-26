#ifndef LEGATO_INIT_SCHEME_H
#define LEGATO_INIT_SCHEME_H

#include "gfx/legato/legato.h"

extern const leScheme WhiteScheme;
extern const leScheme BlackScheme;
extern const leScheme radioButtonScheme;
extern const leScheme activeFansScheme;
extern const leScheme inactiveFansScheme;
extern const leScheme keypadScheme;
extern const leScheme okScheme;
extern const leScheme errorScheme;
extern const leScheme warningScheme;
extern const leScheme progressScheme;
extern const leScheme GENERATED_ClearScheme;
extern const leScheme grayedOutScheme;

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

void legato_initialize_schemes(void);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LEGATO_INIT_SCHEME_H
