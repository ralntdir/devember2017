// Initialization - a handshake with the device
// 1. Enumerate Instance Layer properties
//  Get number of instance layer
uint32_t instanceLayerCount;

// Use seconde parameter as NULL to return the layer count
vkEnumerateInstanceLayerProperties(&instanceLayerCount, NULL);

VkLayerProperties *layerProperty = NULL;
vkEnumerateInstanceLayerProperties(&instanceLayerCount, layerProperty);

// Get the extensions for each available instance layer
forecah layerProperty
{
  VkExtensionProperties *instanceExtensions;
  res = vkEnumerateInstanceExtensionProperties(layer_name, &instanceExtensionCount, instanceExtensions);
}


// 2. Instance Creation
// Vulkan instance object
VkInstance instance;
VkInstanceCreateInfo instanceInfo = {};

// Specify layer names that needs to be enabled on instance.
instanceInfo.ppEnabledLayerNames = { "VK_LAYER_LUNARG_standard_validation", "VK_LAYER_LUNARG_object_tracker" };

// Specify extensions that needs to be enabled on instance.
instanceInfo.ppEnabledExtensionNames = { "VK_KHR_SURFACE_EXTENSION_NAME", "VK_KHR_WIN32_SURFACE_EXTENSION_NAME" };

// Create the Instance object
vkCreateInstance(&instanceInfo, NULL, &instance);

// 3. Enumerate physical devices
VkPhysicalDevice gpu;             // Physical device
uint32_t gpuCount;                // Physical device count
vector<VkPhysicalDevice> gpuList; // List of physical devices

// Get number of GPU count
vkEnumeratePhysicalDevices(instance, &gpuCount, NULL);

// Get GPU information
vkEnumeratePhysicalDevices(instance, &gpuCount, gpuList);

// Swapchain initialization - querying the WSI extension

// 5. Presentation Initialization

// Create an empty Window
CreateWindowEx(...);    // Windows
xcb_create_window(...); // Linux

// Query WSI extensions, store it as function pointers. For example:
// vkCreateSwapchainKHR, vkCreateSwapchain?
// Create an abstract surface object
VkWin32SurfaceCreateInfoKHR createInfo = {};
// VkWaylandSurfaceCreateInfoKHR createInfo = {}; ??
vkCreateWin32SurfaceKHR(instance, &createInfo, NULL, &surface);
// vkCreateWaylandSurfaceKHR(instance, &createInfo, NULL, &surface); ??

// Among all queues, select a queu that supports presentation
foreach Queue in All Queues
{
  vkGetPhysicalDeviceSurfaceSupportKHR(gpu, queueIndex, surface, &isPresentationSupported);

  // Store this queue's index
  if (isPresentationSupported)
  {
    graphicsQueueFamilyIndex = Queue.index;
    break;
  }
}

// Acquire compeitble queue supporting presentation
// and is also a graphics queue
vkGetDeviceQueue(device, graphicsQueueFamilyIndex, 0, &queue);

// Allocate memory for total surface format count
uint32_t formatCount;
vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, surface, &formatCount, NULL);

VkSurfaceformatKHR *surfaceFormats = allocate memory(formatCount * VkSurfaceFormatKHR);

// Grab the surface format into VkSurfaceFormatKHR objects
vkGetPhysicalDevicesSurfaceFormatsKHR(gpu, surface, &formatCount, surfaceFormats);

// Command buffer initialization - allocation command buffers
//
// Resource objects - managing images and buffers
//
// Creating a presentation surface - creating a swapchain

// 6. Creating a Swapchain

// Start recording commands into command buffer
vkBeginCommandBuffer(cm, &cmdBufInfo);

// Getting surface capabilities
vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu, surface, &surfaceCapabilities);

// Retrieve the surface presentation modes
vkGetPhysicalDeviceSurfacePresentModesKHR(gpu, surface, &presentModeCount, NULL);
VkPresentModeKHR presentModes[presentModeCount];
vkGetPhysicalDeviceSurfacePresetnModesKHR(gpu, surface, &presentModeCount, presentModes);

// Creating the Swapchain
VkSwapchainCreateInfoKHR swapChainInfo = {};
fpCreateSwapchainKHR(device, &swapChainInfo, NULL, &swapChain);

// Create the image view of the retrieved swapchaing images
vkGetSwapchainImagesKHR(device, swapChain, &swapchainImageCount, NULL);
VkImage swapchainImages[swapchainImageCount];
vkGetSwapchainImagesKHR(device, swapChain, &swapchainImageCount, swapchainImages);

// Retrieve the Swapchain images
foreach swapchainImages
{
  // Set the implementation compatible layout
  SetImageLayout(...);

  // Insert pipeline barrier
  VkImageMemoryBarrier imgMemoryBarrier = { ... };
  vkCmdPipelineBarrier(cmd, srcStages, destStages, 0, 0, NULL, 0, NULL, 1, &imgMemoryBarrier); //????????

  // Insert pipeline barrier -> como que no
  vkCreateImageView(device, &colorImageView, NULL, &scBuffer.view);

  // Save the image view for application use
  buffers.push_back(scBuffer);
}

// Creating a depth image

// 7. Creating Depth image
// Query supported format features of the physical device
vkGetPhysicalDeviceFormatProperties(gpus, depthFormat, &properties);

// Create and image object
vkCreateImage(device, &imageInfo, NULL, &imageObject);

// Get the memory requirementes for an image resource
vkGetImageMemoryRequirements(device, image, &memRequirements);

// Allocate memory
vkAllocateMemory(device, &memAlloc, NULL, &memorys);

// Bind memory
vkBindImageMemory(device, imageObject, mem, 0);

// Set the implementation compatible layout
SetImageLayout(. . .);

// Insert a pipeline barrier to ensure that specified image
// layout are created before it being used further
vlCmdPipelineBarrier(cmd, srcStages, destStages, 0, 0, NULL, 0, NULL, 1, &imgPipelineBarrier);

// Create an Image View
vkCreateImageView(device, &imgViewInfo, NULL, &view);

// Resource allocation - allocating and binding device memory
//
// Supplying shaders - shader copmilation into SPIR-V

// VERTEX SHADER
#version 450

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 inColor;
layout (location = 0) out vec4 outColor;

out gl_PerVertex
{
  vec4 gl_Position;
};

void main()
{
  outColor = inColor;
  gl_Position = pos;
  gl_Position.y = -glPosition.y;
  gl_Position.z = (gl_Position.z + gl_Position.w) / 2.0;
}

// FRAGMENT SHADER
#version 450

layout(location = 0) in vec4 color;
layout(location = 0) out vec4 outColor;

void main()
{
  outColor = color;
}

// 8. Building shader module

VkPipelineShaderStageCreateInfo vtxShderStages = { ... };
VkShaderModuleCreateInfo moduleCreateInfo = { ... };

// spvVertexShaderData contains binary form of vertex shader
moduleCreateInfo.pCode = spvVertexShaderData;

// Create Shader module on the device
vkCreateShaderModule(device, &moduleCreateInfo, NULL, &vtxShdrStages.module);

// 9. Creating descriptor layout and pipeline layout

// Descriptor layout specifies info type associated with shaders
VkDescriptorSetLayoutBinding layoutBind[2];

layoutBind[0].decriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
layoutBind[0].binding = 0;
layoutBind[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

layoutBind[1].decriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
layoutBind[1].binding = 0;
layoutBind[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

// Use layout bindings and create a descriptor set layout
VkDescriptorSetLayoutCreateInfo descriptorLayout = {};
descriptorLayout.pBindings = layoutBind;

VkDescriptorSetLayout descLayout[2];
vkCreateDescriptorSetLayout(device, &descriptorLayout, NULL, descLayout.data());

// Now use the descriptor layout to create a pipeline layout
VkPipelineLayoutCreateInfo pipelineLayoutCI = { ... };
pipelineLayoutCI.pSetLayouts = descLayout.data();
vkCreatePipelineLayout(device, &pipelineLayoutCI, NULL, &pipelineLayout);

// 10. Render Pass

// Define to attachment for color and depth buffer
VkAttacmentDescription attachments[2];
attachments[0].format = colorImageformat;
attachments[0].loadOp = clear ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_DONT_CARE;
attachments[1].format = depthImageformat;
attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;

VkAttachmentReferece colorReference, depthReference = { ... };

// Describe the subpass, use color image and depth image
VkSubpassDescription subpass = {};
subpass.pColorAttachments = &colorReference;
subpasss.pDepthStencilAttacment = &depthReference;


// Define RenderPass control structure
VkRenderPassCreateInfo rpInfo = { &attachments, &subpass ...};

VkRenderPass renderPass; // Create Render Pass object
vkCreateRenderPass(device, &rpInfo, NULL, &renderPass);

// 11. Creating Frame buffers

VkImageView attachments[2]; // [0] for color, [1] for depth

VkFramebufferCreateInfo fbInfo = {};
fbInfo.renderPass = renderPass; // Pass render buffer object
fbInfo.pAttachments = attachments; // Image view attachments
fbInfo.width = width // Frame buffer width
fbInfo.height = height // Frame buffer height

// Allocate memory for frame buffer objects, for each image
// in the swapchain, there is one frame buffer
VkFramebuffer framebuffers[number of draw image in swapchain]

foreach (drawing buffer in swapchain)
{
  attachments[0] = currentSwapChainDrawImage.view;
  vkCreateFramebuffer(device, &fbInfo, NULL, &framebuffers[i]);
}

// 12. Populates Geometry - storing vertex into GPU memory

static const VertexWithColor triangleData[] =
{
//{     x,     y,    z,    w,    r,    g,    b,   a },
  {  0.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0 },
  { -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0 },
  { -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0 },
};

VkBuffer buffer;
VkMemoryRequirements mem_requirement;
VkDeviceMemory deviceMemory;

// Create buffer object, query required memory and allocate
VkBufferCreateInfo buffer_info = { ... };
vkCreateBuffer(device, &buffer_info, NULL, &buffer);

vkCreateBuffer(device, buffer, &mem_requirement);

VkMemoryAllocateInfo alloc_info = { ... };
vkAllocateMemory(device, &alloc_infom, NULL, &(deviceMemory));

// Copy the triangleData to GPU using mapping and unmapping.
uint8_t *pData;
vkMapMemory(device, deviceMemory, 0, mem_requirement.size, 0, &pData);
memcpy(pData, triangleData, dataSize); // Copyinag data
vkUnmapMemory(device, deviceMemory);

// Bind the allocated memory
vkBindBufferMemory(device, buffer, deviceMemory, 0);

// 13. Vertex binding

VkVertexInputBindingDescription viBinding;
viBinding.binding = 0;
viBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
viBinding.stride = sizeof(triangleData); // data stride

VkVertexInputAttributeDescriptionviAttribs[2];
viAttribs[0].binding = 0;
viAttribs[0].location = 0;
viAttribs[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
viAttribs[0].offset = 0;
viAttribs[1].binding = 0;
viAttribs[1].location = 1;
viAttribs[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
viAttribs[1].offset = 16;

// 14. Defining states

// Vertex Input state
VkPipelineVertexInputStateCreateInfo vertexInputStateInfo = { ... };
vertexInputStateInfo.vertexBindingDescriptionCount = 1;
vertexInputStateInfo.pVertexBindingDescriptions = &viBinding;
vertexInputStateInfo.vertexAttributeDescriptionCount = 2;
vertexInputStateInfo.pVertexAttributeDescriptions = viAttribs;

// Dynamic states
VkPipelineDynamicStateCreateInfo dynamicState = { ... };

// Input assembly state control structure
VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo = { ... };

// Rasterization state control structure
VkPipelineRasterizationStateCreateInfo rasterizationAssemblyInfo = { ... };

// Color blend Attachment state control structure
VkPipelineColorBlendStateCreateInfo colorBlendSI = { ... };

// Color blend state control structure
VkPipelineColorBlendeStateCreateInfo colorBlendStateInfo = { ... };

// View port state control structure
VkPipelineViewportStateCreateInfo viewportStateInfo = { ... };

// Depth stencil state control structure
VkPipelineDepthStencilStateCreateInfo depthStencilStateInfo = { ... };

// Multisampling state control structure
VkPipelineMultisampleStateCreateInfo multiSampleStateInfo = { ... };

// 15. Creating Graphics Pipeline
// Create the pipeline objects
VkPipelineCache pipelineCache;
VkPipelineCacheCreateInfo pipelineCacheInfo;
vkCreatePipelineCache(device, &pipelineCacheInfo, NULL, &pipelineCache);

// Define the control structure of graphics pipeline
VkGraphicsPipelineCreateInfo pipelineInfo;
pipelineInfo.layout = pipelineLayout;
pipelineInfo.pVertexInputState = &vertexInputStateInfo;
pipelineInfo.pInputAssemblyState = &inputAssemblyInfo;
pipelineInfo.pRasterizationState = &rasterStateInfo;
pipelineInfo.pColorBlendState = &colorBlendStateInfo
pipelineInfo.pMultisampleState = &multiSampleStateInfo;
pipelineInfo.pDynamicState = &dynamicState;
pipelineInfo.pViewportState = &viewportStateInfo;
pipelineInfo.pDepthStencilState = &depthStencilStateInfo;
pipelineInfo.pStages = shaderStages;
pipelineInfo.stageCount = 2;
pipelineInfo.renderPasss = renderPass;

// Create graphics pipeline
vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipelineInfo, NULL, &pipeline);

// 16. Acquiring the drawing image

// Define semaphore for synchronizing the acquire of draw image.
// Only acquire draw image when drawing is completed
VkSemaphore imageAcquiredSemaphore;
VkSempahoreCreateInfo imageAcquiredSemaphoreCI = { .... };
imageAcquiredSemaphoreCI.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
vkCreateSemaphore(device, &imageAcquiredSemaphoreCI, NULL, &imageAcquiredSemaphore);

// Get the index of the next available swapchain image:
vkAcquireNextImageKHR(device, sqpChain, UINT64_MAX, imageAcquiredSemaphore, NULL, &swapChainObjCurrentBuffer);

// 17. Preparing render pass control structure

// Define clear color value and depth stencil values
const VkClearValue clearValues[2] = 
{
  [0] = { .color.float32 = { 0.2f, 0.2f, 0.2f, 0.2f } },
  [1] = { .depthStencil = { 1.0f, 0 } },
};

// Render pass execution data structure for a frame buffer
VkRenderPassBeginInfo beginPass;
beginPass.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
beginPass.pNext = NULL;
beginPass.renderPass = renderPass;
beginPass.framebuffer = framebuffers[currentSwapchainImageIndex];
beginPass.renderArea.offset.x = 0;
beginPass.renderArea.offset.y = 0;
beginPass.renderArea.extent.width = width;
beginPass.renderArea.extent.height = height;
beginPass.clearValueCount = 2;
beginPass.pClearValues = clearValues;

// START RENDER PASS
vkCmdBeginRenderPass(cmd, &beginPass, VK_SUBPASS_CONTENTS_INLINE);

// Bind the pipeline
vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
const VkDeviceSize offsets[1] = { 0 };

// Bind the triangle buffer data
vkCmdBindVertexBuffers(cmd, 0, 1, &buffer, offsets);

// viewport = { 0, 0, 500, 500, 0, 1}
vkCmdSetViewport(cmd, 0, NUM_VIEWPORTS, &viewports);

// scissor = { 0, 0, 500, 500 }
vkCmdSetScissor(cmd, 0, NUM_SCISSORS, &scissor);

// Draw command - 3 vertices, 1 instance, 0th first index
vkCmdDraw(cmd, 3, 1, 0, 0);

// END RENDER PASS
vkCmdEndRenderPass(cmd);

// Set the swapchain image layout
setImageLayout(VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL . .);

// COMMAND BUFFER RECORDING ENDS HERE
vkEndCommandBuffer(cmd);

// Queue submission and synchronization - sending jobs
VkFenceCreateInfo fenceInfo = { . . . };
VkFende drawFence;
// Create fence forensuring completion of cmdBuffer processing
vkCreateFende(device, &fenceInfo, NULL, &drawFence);

// Fill the command buffer submission control structures
VkSubmitInfo sbmitInfo[1] = { ... };
submitInfo[0].pNext = NULL;
submitInfo[0].sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
submitInfo[0].pWaitSemaphores = &imageAcquiredSemaphore;
submitInfo[0].commandBufferCount = 1;
submitInfo[0].pCommandBuffers = &cmd;

// Queue the command buffer for execution
vkQueueSubmit(queue, 1, submitInfo, NULL);

// Displaying with presentation layer - rendering a triangle

// Define the presentation control structure
VkPresentInfoKHR present = { ... };
present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
present.pNext = NULL;
present.swapchainCount = 1;
present.pSwapchaings = &swapChain;
present.pImageIndices = &swapCainObjCurrent_buffer;

// Check if all the submitted command buffers are processed
do
{
  res = vkWaitForFences(device, 1, &drawFence, VK_TRUE, FENCE_TIMEOUT);
} while (res == VK_TIMEOUT);

// Handover the swapchain image to presentation queue for presentation purpose
vkQueuePresentKHR(queue, &present);

// Destroy Synchronization objects
vkDestroySemaphore(device, imageAcquiredSemaphore, NULL);
vkDestroyFence(device, drawFence, NULL);
