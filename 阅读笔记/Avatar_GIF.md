##Avatar 自定义GIF[]()

* UI 通过Spine 制作一个动效，然后导出动效（导出资源包括动效需要的：1，图片素材，2，动效描述json）
	
		Spine 是一款针对游戏开发的 2D 骨骼动画编辑工具，
		Spine导出的动效中的素材包括了人物的各个部分，如脸型，眼睛，鼻子，眉毛，发型，眼睛，衣服等等
		通过在运行时替换这些部件即可达到自定义的效果	
* 开源库[YSC_SpineSwiftTest](https://github.com/nikki2pro/YSC_SpineSwiftTest)
* iOS 通过YSC_Spine加载导出的动效将其转成SKNode，然后使用SpriteKit进行播放，在播放的每一帧回调中，将动效帧转成image



		在播放前，根据用户自定义的内容，替换原有素材对应的文件
		通过开源库YSC_Spine加载Spine导出的素材转成SKNode，然后添加到SKScene上（SKScene.addChild(skeleton: SKNode)）
		然后使用SKView对SKScene进行播放（SKView.presentScene(scene: SKScene)）
		SKScene 在每次有更新时都有回调 func update(_ currentTime: CFTimeInterval)
			在更新的回调中可以拿到SKView的纹理SKView.texture，然后转成UIImage
		在每次结束时也有回调func didFinishUpdate()
		
		
* 将获取到的所有动效的帧图片，通过imageIO的接口（CGImageDestinationCreateWithURL）制作成GIF