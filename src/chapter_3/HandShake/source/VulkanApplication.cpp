#include "VulkanApplication.h" 

VulkanApplication::VulkanApplication()
{
  // At application start up, enumerate instance layers
  isntanceObj.layerExtension.getInstanceLayerProperties();
}

~VulkanApplication();

// Wrapper function to create the Vulkan instance
VkResult VulkanApplication::createVulkanInstance(vector<const char*>& layers, vector<const char*>& extensions, const char* applicationName)
{
  instanceObj.createInstance(layers, extensions, applicationName);

  return VK_SUCCESS;
}

VkResult VulkanApplication::enumeratePhysicalDevices(std::vector<VkPhysicalDevice> &gpuList)
{
  // Holds the gpu count
  uint32_t gpuDeviceCount;

  // Get the gpu count
  vkEnumeratePhysicalDevices(instanceObj.instance, &gpuDeviceCount, NULL);

  // Make space for retrieval
  gpuList.resize(gpuDeviceCount);
  // Get Physical device object
  return vkEnumeratePhysicalDevices(instanceObj.instance, &gpuDeviceCount, gpuList.data());
}

void VulkanApplication::initialize()
{
  char title[] = "Hello World!!!";

  // Create the Vulkan instance with specified layer and extension names.
  createVulkanInstance(layerNames, instanceExtensionNames, title);
}
