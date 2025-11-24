# PostgreSQL安装及vs code插件安装

## 一、PostgreSQL 软件安装指南

本指南参考通用标准安装流程（适用于 Windows 环境），与《SQL语法基础》等入门书籍所述步骤基本一致。

### 1. 下载安装包
*   访问 PostgreSQL 官方网站下载页面：[官网下载链接](https://www.enterprisedb.com/downloads/postgres-postgresql-downloads)
*   点击 **"Download the installer"**。
*   在 EnterpriseDB 页面中，选择对应版本的 **Windows x86-64** 下载（建议选择最新的稳定版本，如 17.x 或 18.x）。

### 2. 安装步骤
1.  **运行安装程序**：双击下载的 `.exe` 文件。
2.  **安装目录 (Installation Directory)**：建议保持默认路径（通常为 `C:\Program Files\PostgreSQL\版本号`），点击 Next。
3.  **选择组件 (Select Components)**：确保勾选以下核心组件：
    *   `PostgreSQL Server` (数据库服务核心)
    *   `pgAdmin 4` (官方图形化管理工具，非常有用)
    *   `Command Line Tools` (包含 psql 等命令行工具)
    *   `Stack Builder` (可选，用于安装驱动和附加工具，初学者可暂不关注)
4.  **数据目录 (Data Directory)**：存放数据库实际数据文件的位置，建议保持默认。
5.  **设置密码 (Password)**：**关键步骤！**
    *   为超级用户 `postgres` 设置密码。
6.  **端口设置 (Port)**：默认为 `5432`，保持默认即可。
7.  **区域设置 (Locale)**：建议选择 `[Default locale]`，或者手动选择 `Chinese (Simplified), China` 以支持中文排序规则。
8.  **安装 (Installation)**：确认配置无误后，点击 Next 开始安装。
9.  **完成**：安装结束后，如果提示 "Launch Stack Builder at exit?"，可以**取消勾选**，然后点击 Finish。

### 3. 验证安装
1.  按 `Win` 键，搜索 **"SQL Shell (psql)"** 并打开。
2.  出现命令行窗口，连续按 **Enter** 键接受默认值（Server, Database, Port, Username）。
3.  当提示 `Password for user postgres:` 时，输入刚才设置的密码（输入时不会显示字符），按 Enter。
4.  如果出现 `postgres=#` 提示符，说明安装成功并已连接到数据库。

![安装成功](asset\PostgreSQL\image.png)

---

## 二、VS Code 配置 Database Client 插件

在 VS Code 中连接 PostgreSQL 可以让你在编辑器内直接编写和执行 SQL，无需频繁切换窗口。这里推荐使用 **Database Client** 插件。

### 1. 推荐插件
*   **插件名称**: `Database Client`
*   支持多种数据库（Oracle，PostgreSQL等），界面简洁，功能强大。

### 2. 安装步骤
1.  打开 VS Code，点击左侧侧边栏的 **扩展 (Extensions)** 图标，下载。

### 3. 配置连接
1.  安装完成后，左侧侧边栏会出现一个 **数据库图标 (Database)**，点击它。
2.  点击面板上的 **"Create Connection"** (或者 `+` 号图标)。
3.  在数据库类型列表中选择 **PostgreSQL**。
4.  填写连接详情：
    *   **Host**: `127.0.0.1` 或 `localhost` (本机·)
    *   **Port**: `5432` (默认端口)
    *   **Username**: `postgres`
    *   **Password**: (填写安装时设置的密码)
    *   **Database**: `postgres` (默认管理数据库，也可以填具体的业务数据库名)
    *   **Name**: 给连接起个名字，例如 `Local PG` (可选)
5.  点击 **"Connect"**。
    *   如果连接成功，左侧面板会列出该连接下的数据库和表结构。

### 4. 使用方法
1.  在 Database Client 面板中，展开刚才创建的连接。
2.  点击 **"Open Query"** (或者右键点击数据库/表选择打开查询)。
3.  在打开的 SQL 编辑器中输入 SQL 语句，例如：
    ```sql
    SELECT version();
    ```
4.  点击编辑器上方的 **"Run"** 按钮 (或者使用快捷键，通常是 `Ctrl+Enter`)。
5.  下方会显示查询结果。

![image-1](asset\PostgreSQL\image-1.png)
