#pragma once

#include "Headers.h"

struct LayerProperties
{
  VkLayerProperties properties;
  vector<VkExtensionProperties> extensions;
};

class VulkanLayerAndExtension
{
  // Layers and corresponding extension list
  std::vector<LayerProperties> layerPropertyList;

  // Instance/global layer
  VkResult getInstanceLayerProperties();

  // Global extensions
  VkResult getExtensionsProperties(LayerProperties &layerProps, VkPhysicalDevice *gpu=NULL);

  // Device base extensions
  VkResult getDeviceExtensionProperties(VkPhysicalDevice *gpu);
}

