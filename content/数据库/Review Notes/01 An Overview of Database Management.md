## 重点

- 1.2 数据层级 (Data Hierarchy)
- 2.2 数据库方法的优势 (Benefits of the Database Approach)
- 3. 数据库系统的组成 (Components of the Database System)
- 4. 数据库语言 (Database Languages)
- 5. 数据模型 (Data Models)
- 6. 数据独立性 (Data Independence)

---
## 1. 核心概念定义

### 1.1 什么是数据库系统？ (What is a Database System?)

数据库系统不仅仅是数据的集合，它可以从以下四个角度进行定义：
1. **计算机化的记录保持系统 (Computerized Record-keeping System)**:
- 相当于一个电子文件柜，允许用户按需存储、检索和更新信息。
2. **逻辑相关数据的共享集合 (Shared Collection of Logically Related Data)**
- 旨在满足组织的各种信息需求。
3. **持久数据的集合 (Collection of Persistent Data):** 
- 数据只有在收到明确的删除请求时才会被移除（区别于程序运行时的临时数据）。
4. **真命题的集合 (Collection of True Propositions):** 
- 从逻辑学角度看，数据库存储的是既定的事实（Facts），由此可以推导出更多的事实。

### 1.2 数据层级 (Data Hierarchy)

*   **字符 (Character):** 最小的信息单位。
*   **字段 (Field):** 一组相关的字符。
*   **记录 (Record):** 一组相关的字段（Rows）。
*   **文件 (File):** 一组相关的记录（Table）。
*   **数据库 (Database):** 一组逻辑相关的文件。
*   **数据仓库 (Data Warehouse):** 来自多个数据库的信息集合。

---

## 2. 为什么要使用数据库？ (Why Database?)

### 2.1 传统文件系统的局限性 (Limitations of File-Based Approach)

在数据库出现之前，应用程序独立管理自己的数据文件，导致了以下问题：
*   **数据分散与隔离 (Separation and Isolation):** 数据分散在不同文件中，难以整合。
*   **数据冗余 (Data Duplication):** 相同数据存在多处，浪费空间且导致不一致。
*   **数据依赖性 (Data Dependence):** 应用程序依赖于特定的文件格式，文件结构改变需修改程序。
*   **不兼容性 (Incompatibility):** 不同程序可能使用不兼容的文件格式。
*   **难以实现共享与安全 (Difficulty in Sharing & Security):** 难以控制多用户并发访问和数据安全性。

### 2.2 数据库方法的优势 (Benefits of the Database Approach)

数据库方法的核心思想是**首先设计应用的数据，然后再编写程序来处理它**。其主要优势包括：
*   **数据共享 (Data Sharing):** 多个用户和应用可同时访问数据。
*   **减少冗余 (Redundancy Reduced):** 避免不必要的数据重复。
*   **避免不一致 (Inconsistency Avoided):** 通过控制冗余，防止同一数据在不同地方值不同。
*   **支持事务 (Transaction Support):** 保证操作的原子性（逻辑工作单元）。
*   **完整性维护 (Integrity Maintained):** 确保数据的正确性。
*   **安全性增强 (Security Enforced):** 控制数据访问权限。
*   **标准化 (Standards Enforced):** 统一数据表示，便于交换。

---

## 3. 数据库系统的组成 (Components of the Database System)

> 2022DB 填空题 1

数据库系统由四个主要部分组成：

### 3.1 数据 (Data)

*   **集成 (Integrated):** 统一不同文件，消除冗余。
*   **共享 (Shared):** 多用户并发访问。
*   **持久 (Persistent):** 数据长期存储。

### 3.2 硬件 (Hardware)

包括存储数据的**辅助存储器**（如磁盘）以及运行软件的**处理器和主内存**。

### 3.3 软件 (Software)

*   **数据库管理系统 (DBMS - Database Management System):** 最核心的软件组件，负责管理和控制对数据库的访问。常见的DBMS包括 Oracle, SQL Server, DB2, MySQL 等。
*   **应用开发工具:** 用于设计、报表生成等。

### 3.4 人员 (People)

*   **数据管理员 (DA - Data Administrator):** 属于管理者。负责决定存储什么数据以及制定数据维护的**策略**。
*   **数据库管理员 (DBA - Database Administrator):** 属于技术专家。负责根据DA的策略**创建数据库**并实施技术控制（如性能监控、安全性实施）。
*   **应用程序员 (Application Programmers):** 使用编程语言（如Java, COBOL）开发应用。
*   **终端用户 (End Users):** 通过在线应用或接口访问数据的人。

---

## 4. 数据库语言 (Database Languages)

**SQL (Structured Query Language):** 结构化查询语言，是现代数据库系统的标准语言。

*   **DDL (Data Definition Language):** 数据定义语言。用于定义数据库结构（如 `CREATE TABLE`）。
*   **DML (Data Manipulation Language):** 数据操纵语言。用于访问和处理数据（查询语言）。
    *   **过程化语言 (Procedural):** 用户指定需要什么数据以及**如何**获取。
    *   **非过程化语言 (Non-procedural):** 用户仅指定需要什么数据，**无需指定如何**获取（SQL属于此类）。
*   **DCL (Data Control Language):** 数据控制语言。

---

## 5. 数据模型 (Data Models)

数据模型是对象（数据结构）和操作符（行为）的抽象定义。

1.  **层次模型 (Hierarchical Model):** 树状结构（如IBM IMS）。特点是有且仅有一个根节点，其他节点仅有一个父节点。只能处理一对多关系。
2.  **网状模型 (Network Model):** 图状结构。一个节点可以有多个父节点，支持多对多关系。
3.  **关系模型 (Relational Model):** 数据表示为**表 (Tables)** 中的行。基于逻辑和数学，是目前最主流的模型。
4.  **对象/关系模型 & 对象模型 (Object-Oriented/Relational):** 引入面向对象技术（如继承、多态），适用于复杂数据结构和多媒体应用。

---

## 6. 数据独立性 (Data Independence)

数据独立性是数据库系统的主要目标之一，指在不影响上层应用的情况下修改下层模式的能力。

*   **物理数据独立性 (Physical Data Independence):** 指在不改变应用程序（逻辑视图）的情况下，改变数据的**物理表示**（存储方式）或**访问技术**（如索引、哈希）的能力。
    *   例如：将数字存储格式从十进制改为二进制，或者添加索引以提高性能，应用程序无需修改代码。
*   **逻辑数据独立性 (Logical Data Independence):** (虽然源文件主要详述了物理独立性，但提到了逻辑与物理的区别) 指改变概念模式而不影响外部模式或应用程序的能力。

---

## 7. 数据库发展简史 (History Highlights)

*   **1960s:** 文件系统为主；1968年 IMS (层次模型) 诞生。
*   **1970:** **E.F. Codd** 提出**关系模型 (Relational Model)**，奠定了现代数据库的理论基础。
*   **1976:** Peter Chen 提出 E-R 模型 (实体-关系模型)。
*   **1980s:** SQL 标准化；商业关系数据库 (如 DB2, Oracle) 爆发。
*   **2000s+:** NoSQL 数据库兴起 (BigTable, Dynamo, MongoDB 等)。
