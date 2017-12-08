#pragma once

#include "VulkanInstance.h"
#include "VulkanLayerAndExtension.h" 

class VulkanApplication
{
  private:
    // CTOR: Application constructor responsible for layer enumeration
    VulkanApplication();
  public:
    // DTOR
    ~VulkanApplication();

  public:
    // Create the Vulkan instance object
    VkResult createVulkanInstance(vector<const char*>& layers, vector<const char*>& extensions, const char* applicationName);

    VkResult enumeratePhysicalDevices(std::vector<VkPhysicalDevice> &gpuList);

    // Vulkan Instance object
    VulkanInstance instanceObj;
};
