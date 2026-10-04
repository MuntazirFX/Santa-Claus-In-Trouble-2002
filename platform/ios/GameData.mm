#import "GameData.h"

NSString* GameDataPath(NSString* rel) {
    NSString* bundled = [[[NSBundle mainBundle].resourcePath
        stringByAppendingPathComponent:@"assets"] stringByAppendingPathComponent:rel];

    if (![rel isEqualToString:@"config.txt"] && ![rel isEqualToString:@"score.dat"])
        return bundled;                                   // read-only data

    NSString* docs = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES).firstObject;
    NSString* dest = [docs stringByAppendingPathComponent:rel];
    NSFileManager* fm = NSFileManager.defaultManager;
    if (![fm fileExistsAtPath:dest])
        [fm copyItemAtPath:bundled toPath:dest error:nil];
    return dest;                                          // writable copy
}
