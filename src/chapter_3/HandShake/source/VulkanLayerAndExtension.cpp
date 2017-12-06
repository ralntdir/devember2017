#include "VulkanLayerAndExtension.h"

VulkanLayerAndExtension::VulkanLayerAndExtension()
{
}

VulkanLayerAndExtension::~VulkanLayerAndExtension()
{
}

VkResult VulkanLayerAndExtension::getInstanceLayerProperties()
{
  // Store numbers of instance layers
  uint32_t instanceLayerCount;
  // Vector to store layer properties
  std::vector<VkLayerProperties> layerProperties;
  // Check Vulkan API result status
  VkResult result;

  // Query all the layers
  do
  {
    result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, NULL);

    if (result)
    {
      return result;
    }

    if (instanceLayerCount == 0)
    {
      return VK_INCOMPLETE; // return fail
    }

    layerProperties.resize(instanceLayerCount);
    result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, layerProperties.data());
  } while (result == VK_INCOMPLETE);

  // Query all the extensions for each layer and store it.
  std::cout << "\nInstanced Layers" << std::endl;
  std::cout << "===================" << std::endl;

  for (auto globalLayerProp: layerProperties)
  {
    // Print layer name and its description
    std::cout << "\n" << globalLayerProp.description << "\n\t|\n\t|---[Layer Name]--> " << globalLayerProp.layerName << "\n";

    LayerProperties layerProps;
    layerProps.properties = globalLayerProp;

    // Get Instance level extensions for corresponding layer properties
    result = getExtensionProperties(layerProps);

    if (result)
    {
      continue;
    }

    layerPropertiesList.push_back(layerProps);

    // Print extension name for each instance layer
    for (auto j : layerProps.extensions)
    {
      std::cout << "\t\t|\n\t\t|---[Layer Extensions]---> " << j.extensionName << "\n";
    }
  }

  return result;
}

// This function retrieves extension and its properties at instance and device level.
// Pass a valid physical device pointer (gpu) to retrieve device leven extensions, 
// otherwise use NULL to retrieve extension specific to instance level.
VkResult VulkanLayerAndExtension::getExtensionProperties(LayerProperties &layerProps, VkPhysicalDevice *gpu)
{
  // Stores number of extension per layer
  uint32_t extensionCount;
  VkResult result;

  // Name of the layer
  char* layerName = layerProps.properties.layerName;

  do
  {
    // Get the total number of extension in this layer
    if (gpu)
    {
      result = vkEnumerateDeviceExtensionProperties(*gpu, layerName, &extensionCount, NULL);
    }
    else
    {
      result = vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, NULL);
    }

    if (result || extensionCount == 0)
    {
      continue;
    }

    layerProps.extensions.resize(extensionCount);

    // Gather all extension properties
    if (gpu)
    {
      result = vkEnumerateDeviceExtensionProperties(*gpu, layerName, &extensionCount, layerProps.extensions.data());
    }
    else
    {
      result = vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, layerProps.extensions.data());
    }

  } while (result == VK_INCOMPLETE);
