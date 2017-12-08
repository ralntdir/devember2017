#include "Headers.h"
#include "VulkanApplication.h"

std::vector<const char *> instanceExtensionNames =
{
  // TODO(ralntdir): change the extension name to the corresponding one for linux
  VK_KHR_SURFACE_ETENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME
};

std::vector<const char *> instanceLayerNames = 
{
  "VK_LAYER_LUNARG_api_dump"
};

int main(int argc, char **argv)
{
  VkResult res;

  // Create singleton object, calls Constructor function
  VulkanApplication *appObj = VulkanApplication::GetInstance();
  appObj->initialize();
  return 0;
}
