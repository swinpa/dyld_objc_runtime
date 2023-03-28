# rvm、Ruby、gem、CocoaPods
##[rvm定义](https://ruby-china.org/wiki/rvm-guide) 
* RVM 是一个命令行工具，可以提供一个便捷的多版本 Ruby 环境的管理和切换。

* [Ruby](https://www.runoob.com/ruby/ruby-intro.html)

##[gem定义](https://www.runoob.com/ruby/ruby-rubygems.html)
* Gem 是 Ruby 模块 (叫做 Gems) 的包管理器。其包含包信息，以及用于安装的文件

##[CocoaPods定义](https://cocoapods.org)
* cocoapods 安装 --> [说明](https://guides.cocoapods.org/using/getting-started.html#getting-started)

##[Homebrew](https://brew.sh/index_zh-cn)

##[Fastlane 安装配置](https://docs.fastlane.tools/getting-started/ios/setup/)
##蒲公英

* Fastlane和蒲公英结合[参考](https://www.pgyer.com/doc/view/fastlane)
fastlane需要写fastlane的task来配置打包信息，比如scheme，profile，蒲公英api_key等

```
# This file contains the fastlane.tools configuration
# You can find the documentation at https://docs.fastlane.tools
#
# For a list of all available actions, check out
#
#     https://docs.fastlane.tools/actions
#
# For a list of all available plugins, check out
#
#     https://docs.fastlane.tools/plugins/available-plugins
#

# Uncomment the line if you want fastlane to automatically update itself
# update_fastlane

default_platform(:ios)

platform :ios do
  desc "Pgyer Development"
  lane :custom_lane do
    # add actions here: https://docs.fastlane.tools/actions
  end

  lane :pgyer_development do
    build_app(
      scheme: "KLChat",
      export_method: "development",
      clean: true,
      silent: true,
      export_options: {
        provisioningProfiles: {
          "mobi.koalachat.app" => "koalachat development"
        }
      }
    )
    pgyer(api_key: "1bc67c30343e480ba456d8fdb316a8aa", password: "123456", install_type: "2")
   end

end

```
打包：控制台输入：fastlane pgyer_development（也就是对应的lane(task)）

