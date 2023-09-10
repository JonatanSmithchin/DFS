项目结构问题不大

# Namenode

1. 元数据管理 block 目录children结构可以改进
2. datanode管理
3. 与client交互
4. block 重点

# Datanode

1. 与Namenode交互的client模块
   - 心跳报告
   - 处理返回的命令

2. 与Client交互传输数据的模块 重点

3. 管理datanode上的数据块的模块

# Client

1. 与datanode交互
2. 安全性：加密block
3. 与namenode交互
4. 接受block块 重点