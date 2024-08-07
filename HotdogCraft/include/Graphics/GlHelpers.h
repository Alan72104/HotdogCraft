#include <glad/glad.h>
#include <source_location>
#include <string>

namespace HotdogCraft
{
    namespace Graphics
    {
        namespace GlHelpers
        {
            void checkError(std::source_location loc = std::source_location::current());
            std::string getErrorName(GLenum e);
            std::string getTypeName(GLenum e);
        }
    }
}