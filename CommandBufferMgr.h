//
// Created by 王海明 on 2021/7/27.
//

#pragma once

#include "VulkanHeader.h"


class CommandBufferMgr {

public:
    static void allocCommandBuffer(const VkDevice *device, const VkCommandPool cmdPool, VkCommandBuffer *cmdBuf,
                                   const VkCommandBufferAllocateInfo *commandBufferAllocateInfo);

    static void beginCommandBuffer(VkCommandBuffer cmdBuf, VkCommandBufferBeginInfo *inCmdBufInfo = nullptr);

    static void endCommandBuffer(VkCommandBuffer cmdBuf);

    static void submitCommandBuffer(const VkQueue &queue, const VkCommandBuffer *cmdBufList,
                                    const VkSubmitInfo *submitInfo = nullptr, const VkFence fence = VK_NULL_HANDLE);
};


