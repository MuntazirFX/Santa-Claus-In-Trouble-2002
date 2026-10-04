#import <Foundation/Foundation.h>

// Original install folder jaisa layout: xmas.xpk, config.txt, score.dat, music/m02B.wav
// relativePath example: @"xmas.xpk", @"music/m02B.wav"
// config.txt aur score.dat likhne layak hain, isliye pehli baar Documents mein copy hote hain.
NSString* GameDataPath(NSString* relativePath);
