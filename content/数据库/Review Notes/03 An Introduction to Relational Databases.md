## 重点

- 1.2 数据抽象的三个层次 (Levels of Data Abstraction)
- 2.1 术语对照表 (Terminology Mapping)
- 2.3 关系的性质 (Properties of Relations)
- 3. 关系模型的三个方面 (Three Aspects of Relational Model)

---
## 1. 数据模型概述 (Data Model Overview)

### 1.1 定义

数据模型是对对象（Objects）和操作符（Operators）的抽象、自包含的逻辑定义。

*   **对象 (Objects):** 模拟数据的结构（如数据类型、关系和约束）。
*   **操作符 (Operators):** 模拟对象的行为。

### 1.2 数据抽象的三个层次 (Levels of Data Abstraction)

> 这个和三级架构有区别。

1.  **概念层 (Conceptual Level):** 高层抽象，接近用户感知数据的方式。例如：实体-关系模型 (ER Model)、语义对象模型。
2.  **逻辑层 (Logical Level / DBMS Level):** 接近数据的组织方式，但仍可被用户理解。例如：关系模型 (Relational)、面向对象模型、网状模型、层次模型。
3.  **物理层 (Physical Level):** 描述数据在计算机中存储的细节。

### 1.3 关系模型历史

*   由 **E.F. Codd** 于 1970 年提出，基于域（Domain）和关系（Relation）的数学概念,。

---
## 2. 关系模型核心概念 (Relational Model Concepts)

### 2.1 术语对照表 (Terminology Mapping)

> 2022DB 填空题 2 （考术语我真服了）

| 形式化术语 (Formal)       | 常用术语 (Common/Physical) | 定义与说明                   |
| :------------------- | :--------------------- | :---------------------- |
| **Relation** (关系)    | Table (表)              | 数据的集合，逻辑结构。             |
| **Tuple** (元组)       | Row / Record (行/记录)    | 对象属性值的集合。               |
| **Attribute** (属性)   | Column / Field (列/字段)  | 数据的特征维度。                |
| **Cardinality** (基数) | Number of rows (行数)    | 关系中元组的个数。               |
| **Degree** (度/目)     | Number of columns (列数) | 关系中属性的个数。               |
| **Domain** (域)       | Data Type (数据类型)       | 属性可能取值的集合。它是对格式和语义的描述,。 |

### 2.2 关键约束 (Key Constraints)（详见[[07 Integrity]]）

*   **主键 (Primary Key):** 唯一标识关系中每个元组的一个属性或属性组。主键值不能为空且不能重复,。
*   **外键 (Foreign Key):** 一个关系中的属性（组），它是另一个相关关系的主键。用于建立关系之间的联系。

### 2.3 关系的性质 (Properties of Relations)

一个标准的关系（表）必须满足以下性质,：

1.  **无重复元组 (No duplicate tuples):** 表中没有完全相同的两行（主键约束、Index）。
2.  **元组无序 (Tuples are unordered):** 行的顺序不重要（从上到下）。
3.  **属性无序 (Attributes are unordered):** 列的顺序不重要（从左到右）。
4.  **原子性 (Atomicity):** 每个元组的每个属性只包含一个值（即第一范式 1NF）。

---
## 3. 关系模型的三个方面 (Three Aspects of Relational Model)

### 3.1 结构方面 (Structural Aspect)

*   数据以 **表 (Tables)** 的形式呈现。
*   **信息原则 (The Information Principle):** 数据库中的全部信息内容仅用一种方式表示，即表中的行和列位置上的显式值。**不使用指针**连接表。
*   表是逻辑结构，物理存储可以是堆文件、索引、哈希等，系统可以自由选择。

### 3.2 完整性方面 (Integrity Aspect)

*   **实体完整性 (Primary Key Constraints):** 主键唯一且非空。
*   **域完整性 (Domain Constraints):** 属性值必须符合域的定义（如数据类型、取值范围）。
*   **参照完整性 (Referential Integrity Constraint):** 外键必须引用另一个关系中已存在的元组，保证数据一致性。

### 3.3 操作方面 (Manipulative Aspect)

*   **闭包性质 (Closure Property):** 关系操作的输入是关系，输出也是关系（表）。这使得操作可以嵌套。
*   **非过程化 (Non-procedural):** 用户只需指定“做什么”（What），而无需指定“怎么做”（How）。系统负责自动导航,。
*   主要操作包括：限制 (Restrict/Select)、投影 (Project)、连接 (Join)。

---
## 4. 关系变量与视图 (Relvars & Views)

### 4.1 关系变量 (Relvar - Relational Variable)

> 关系变量与关系值的讨论会在 [[08 Functional Dependencies]] 中进一步讨论

*   **定义:** 在不同时间可能具有不同值的变量。我们常说的“表”实际上是关系变量，而特定时刻表中的数据是**关系值**。
*   **操作:** 如赋值、插入、删除等改变关系变量的值。

### 4.2 基本关系变量 (Base Relvars)

*   **定义:** 原始的、实际存储的表（Real relvar）。

### 4.3 视图 (Views)

> 2022 填空题 7
> 视图是根据 **用户需求**（或 用户的需要）设计的，是从一个或多个 **基本表** 或 **视图** 导出的。

*   **定义:** 派生关系变量（Derived/Virtual relvar）。它不存储实际数据，而是由基本表通过查询定义生成的虚拟表。
*   **本质:** 它是通往底层基本数据的“窗口”。对视图的修改会自动反映到基本表（反之亦然）。
*   **优点:**
    1.  简化用户操作。
    2.  提供同一数据的多种视角。
    3.  提供逻辑数据独立性（重构数据库时）。
    4.  数据安全保护（隐藏敏感字段）。

---

## 5. 系统组件 (System Components)

> 2022 填空题 8
### 5.1 优化器 (Optimizer)

*   由于关系语言是非过程化的，系统需要**优化器**来决定最有效的执行路径（例如是全表扫描还是使用索引）。
*   优化依据：表的大小、索引的选择性、物理聚簇情况等。

### 5.2 数据字典/目录 (Data Dictionary / Catalog)

*   **内容:** 存储关于数据库对象的详细信息（元数据 Metadata），如模式定义、映射关系、安全约束等。
*   **特点:** 目录本身也是由系统关系变量（表）组成的，用户可以像查询普通数据一样查询目录。
-   **例**：user_tables, user_indexes, user_sequences, user_constrains 是数据字典中面向用户的视图。

---

## 6. 事务 (Transactions)

### 6.1 定义

事务是一个逻辑工作单元，通常包含多个数据库操作。事务要么全部执行，要么全不执行,。
*   **COMMIT:** 提交事务，确保持久化。
*   **ROLLBACK:** 回滚事务，撤销操作。

### 6.2 ACID 属性

*   **原子性 (Atomic):** 事务不可分割，要么全做，要么全不做。
*   **一致性 (Consistency):** (虽然源文件未详细展开，但通常指事务将数据库从一个一致状态转换到另一个一致状态)。
*   **隔离性 (Isolation):** 未提交的更新对其他事务不可见。
*   **持久性 (Durability):** 一旦提交，更新永久生效，即使系统崩溃。

### 6.3 并发控制 (Concurrency)

*   **序列化 (Serialization):** 并发执行的一组事务的结果必须与某种串行执行顺序的结果相同，才被认为是正确的。
*   **并发方式:**
    *   **交叉并发 (Interleaved):** 单处理器上轮流执行。
    *   **同时并发 (Simultaneous):** 多处理器上真正并行,。
*   **目的:** 提高资源利用率，改善短事务的响应时间,。
