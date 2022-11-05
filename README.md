# HostedNetworkConfigurator（承载网络配置工具）
## 功能
- 在 Windows 设备上快捷地启动承载网络，无需手动输入命令。
- 保存配置，以便下次使用。
## 使用方法
1. 设置SSID（无线局域网络名称）和KEY（无线局域网络密码，应为 8 到 63 个 ASCII 字符组成的字符串），其他选项可保持默认。
2. 单击“执行命令”，等待命令执行完成。
3. 单击“设置网络共享”（或打开“控制面板\网络和 Internet\网络连接”），弹出窗口后选择有正常网络连接的适配器，右键单击，选择“属性”，选择“共享”标签页，勾选“允许其他网络用户通过此计算机的 Internet 连接来连接(N)”复选框，在“家庭网络连接(H)”处选择描述为 Microsoft Virtual WiFi Miniport Adapter 的适配器名称（在上级窗口可查看名称，一般为“无线网络连接 2”），点击确定，关闭子窗口。
4. 回到本程序，单击“启动承载网络”，等待命令执行完成。
## 注意事项
- 须先启用网络共享，再启动承载网络。否则，承载网络可能无 Internet 访问，重复第3、4步即可解决。
- 系统无线适配器必须支持承载网络。单击“显示无线 LAN 驱动属性”，若显示“支持的承载网络  : 是”，即为支持，反之为不支持。
## 下载已编译的二进制程序
- [GitHub](https://github.com/MCjiaozi/HostedNetworkConfigurator/releases)
- [发布网站](https://www.mcjiaozi.com/hostednetworkconfigurator/)
