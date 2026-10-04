#import "GameViewController.h"
#import <MetalKit/MetalKit.h>
#import "Renderer.h"
#import "GameData.h"
#include "core/xpk.h"

@implementation GameViewController {
    MTKView*   _view;
    Renderer*  _renderer;
    XpkPackage _pkg;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    _view = [[MTKView alloc] initWithFrame:self.view.bounds device:MTLCreateSystemDefaultDevice()];
    _view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    _view.preferredFramesPerSecond = 60;
    [self.view addSubview:_view];

    _renderer = [[Renderer alloc] initWithView:_view];
    _view.delegate = _renderer;

    // xmas.xpk bundle ke andar se kholo
    NSString* path = GameDataPath(@"xmas.xpk");
    NSString* msg = _pkg.Open(path.UTF8String)
        ? [NSString stringWithFormat:@"xmas.xpk OK: %zu files", _pkg.Count()]
        : @"xmas.xpk nahi mila";

    UILabel* label = [[UILabel alloc] initWithFrame:CGRectMake(16, 16, 420, 24)];
    label.text = msg;
    label.textColor = UIColor.whiteColor;
    [self.view addSubview:label];
}

- (BOOL)prefersStatusBarHidden { return YES; }
- (UIInterfaceOrientationMask)supportedInterfaceOrientations { return UIInterfaceOrientationMaskLandscape; }
@end
