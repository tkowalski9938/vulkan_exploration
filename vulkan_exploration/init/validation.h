#include <stdbool.h>
#include <stdint.h>

// returns true if supports validation layers needed
bool checkValidationLayerSupport(void);

extern const bool enableValidationLayers;

extern const char *validationLayers[];

extern const uint32_t numValidationLayers;
