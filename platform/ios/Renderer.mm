#import "Renderer.h"

@implementation Renderer {
    id<MTLCommandQueue> _queue;
}

- (instancetype)initWithView:(MTKView*)view {
    if ((self = [super init])) {
        _queue = [view.device newCommandQueue];
        view.clearColor = MTLClearColorMake(10.0/255, 20.0/255, 60.0/255, 1.0);
        view.depthStencilPixelFormat = MTLPixelFormatDepth32Float;
    }
    return self;
}

- (void)drawInMTKView:(MTKView*)view {
    MTLRenderPassDescriptor* rpd = view.currentRenderPassDescriptor;
    id<CAMetalDrawable> drawable = view.currentDrawable;
    if (!rpd || !drawable) return;

    id<MTLCommandBuffer> cb = [_queue commandBuffer];
    id<MTLRenderCommandEncoder> enc = [cb renderCommandEncoderWithDescriptor:rpd];
    // TODO: level meshes, Santa, UI yahan draw honge
    [enc endEncoding];
    [cb presentDrawable:drawable];
    [cb commit];
}

- (void)mtkView:(MTKView*)view drawableSizeWillChange:(CGSize)size {}
@end
