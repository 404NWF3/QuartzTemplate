## 重点

- 全是重点，考前复习一下5个实验报告

## 1. SQL 语言概览 (Overview)

SQL 包含两大类操作：
*   **数据定义语言 (DDL):** 用于定义数据库模式（Schema）。
*   **数据操纵语言 (DML):** 用于查询和更新数据。
---
## 2. 基础查询结构 (Basic Query Structure)

标准的 SQL 查询结构由三个子句组成，其结果也是一个关系（表）。

### 2.1 SELECT 子句

*   **对应操作:** 对应关系代数中的 **投影 (Projection)**。
*   **功能:** 列出查询结果中需要的属性。
*   **去重 (Distinct):** SQL 默认允许重复元组。使用 `select distinct` 强制去除重复行。
*   **全部属性:** 使用星号 `*` 表示所有属性 (`select *`)。
*   **算术表达式:** 支持 `+, -, *, /` 运算。

### 2.2 WHERE 子句

*   **对应操作:** 对应关系代数中的 **选择 (Selection)**。
*   **功能:** 指定筛选条件。
*   **逻辑运算符:** `AND`, `OR`, `NOT`。
*   **范围查询:** 使用 `BETWEEN ... AND ...`。

### 2.3 FROM 子句

*   **对应操作:** 对应关系代数中的 **笛卡尔积 (Cartesian Product)**。
*   **功能:** 列出查询涉及的关系（表）。

### 2.4 其他重要操作

*   **重命名 (Rename):** 使用 `AS` 子句为关系或属性起别名 (`old-name as new-name`)。
*   **元组变量 (Tuple Variables):** 在 `FROM` 子句中使用 `AS` 定义表的别名（如 `from branch as T`），常用于自连接。
*   **字符串匹配 (String Operations):** 使用 `LIKE` 操作符。
    *   `%`: 匹配任意子串。
    *   `_`: 匹配任意单个字符。
*   **排序 (Ordering):** `ORDER BY` 子句。
    *   `ASC`: 升序（默认）。
    *   `DESC`: 降序。
---
## 3. 集合操作 (Set Operations)

SQL 支持标准的集合操作，且**自动去除重复项**。

*   **UNION (并集):** 两个查询结果的并集。
*   **INTERSECT (交集):** 两个查询结果的交集。
*   **MINUS (差集):** 第一个查询结果减去第二个查询结果（在某些系统中称为 EXCEPT）。
---
## 4. 聚集函数与分组 (Aggregate Functions & Grouping)

### 4.1 聚集函数 (Aggregate Functions)

对一列值进行计算并返回单个值：
*   `AVG()`: 平均值。
*   `MIN()`: 最小值。
*   `MAX()`: 最大值。
*   `SUM()`: 求和。
*   `COUNT(*)`: 统计行数（包括空值）。
*   `COUNT(DISTINCT column)`: 统计非空且不重复的值的数量。

### 4.2 分组 (Group By)

*   **语法:** `GROUP BY column-name`。
*   **规则:** `SELECT` 子句中未包含在聚集函数中的属性，**必须**出现在 `GROUP BY` 列表中。

### 4.3 Having 子句

*   **功能:** 对**分组后**的结果进行筛选。
*   **区别:** `WHERE` 作用于元组（分组前），`HAVING` 作用于组（分组后）。
*   **示例:** 找出平均余额大于 600 的支行。

```sql
select branch-name, avg(balance)
from account
group by branch-name
having avg(balance) > 600;
```
---
## 5. 空值 (Null Values)

*   **定义:** `null` 表示未知值 (unknown) 或不存在的值。
*   **运算规则:**
    *   任何涉及 `null` 的算术表达式结果为 `null`。
    *   涉及 `null` 的比较运算返回 **unknown** (非 true 也非 false)。
*   **三值逻辑 (Three-Valued Logic):** True, False, Unknown。
    *   `OR`: (unknown or true) = true。
    *   `AND`: (true and unknown) = unknown; (false and unknown) = false。
*   **处理:** `WHERE` 子句将 `unknown` 视为 `false`。
*   **检测:** 使用 `IS NULL` 测试。
*   **聚集函数:** 除 `COUNT(*)` 外，其他聚集函数都会**忽略**空值。

---
## 6. 嵌套子查询 (Nested Subqueries)

子查询是嵌套在另一个查询中的 `SELECT-FROM-WHERE` 表达式。

### 6.1 集合成员资格 (Set Membership)
*   **IN / NOT IN:** 测试元素是否在集合中。
    *   例如：找出既有贷款又有存款的客户（交集的一种实现方式）。

### 6.2 集合比较 (Set Comparison)
*   **SOME:** 至少比集合中的某一个大/小 (`> some` 等价于 `> min`)。
*   **ALL:** 比集合中的所有都大/小 (`> all` 等价于 `> max`)。

### 6.3 空关系测试 (Test for Empty Relations)
*   **EXISTS:** 如果子查询非空，返回 `true`。
*   **NOT EXISTS:** 如果子查询为空，返回 `true`。
*   **应用:** 常用于实现“全称量词”查询（如：选修了**所有**课程的学生），通过双重否定逻辑实现（没有一门课是他不选修的）。
---
## 7. 数据库修改 (Modification of the Database)

*   **删除 (Deletion):** `DELETE FROM table WHERE ...`。
    *   可以基于子查询删除一组元组。
*   **插入 (Insertion):**
    *   插入指定值: `INSERT INTO table VALUES (...)`。
    *   插入查询结果: `INSERT INTO table SELECT ...`。
*   **更新 (Update):** `UPDATE table SET column = expression WHERE ...`。
    *   **注意:** 执行顺序很重要（如分段调整工资时）。

---
## 8. 数据定义语言 (Data Definition Language - DDL)

### 8.1 创建表 (Create Table)
语法：`CREATE TABLE r (A1 D1, ..., constraints)`。
*   **完整性约束 (Integrity Constraints):**
    *   `NOT NULL`: 非空。
    *   `PRIMARY KEY (A1, ...)`: 主键（自动隐含非空）。
    *   `CHECK (P)`: 检查条件（如 `check (assets >= 0)`）。

### 8.2 删除与修改表
*   **DROP TABLE:** 删除表及其所有数据。
*   **ALTER TABLE:**
    *   `ADD A D`: 增加新列（旧数据该列设为 null）。
    *   `DROP A`: 删除列。
---
## 9. 视图 (Views)

*   **定义:** 视图是虚表，通过查询定义，不存储实际数据，只存储定义。
*   **语法:** `CREATE VIEW v AS <query expression>`。
*   **作用:** 隐藏数据细节，简化查询。
*   **更新限制:** 并非所有视图都可以更新。以 DB2 为例，以下情况**不允许**更新视图：
    1.  由两个以上基本表导出。
    2.  包含表达式或常数（但允许 DELETE）。
    3.  包含聚集函数。
    4.  包含 `GROUP BY` 或 `DISTINCT`。
    5.  定义中包含嵌套查询。
---
## 写查询语句时要注意

### 1. 特殊函数

实验报告中涉及了多种用于处理日期、字符串、数值以及处理空值的Oracle SQL特殊函数。

**日期与时间处理函数：**
* **`TO_DATE`**: 用于将字符串转换为日期格式。
    *  `TO_DATE('2014-03-10', 'YYYY-MM-DD')
* **`TO_CHAR`**: 用于将日期转换为字符串，常用于提取特定的月份或年份。
    *  `WHERE TO_CHAR(HIREDATE, 'MM') = '05'` 
* **`EXTRACT`**: 用于从日期中提取特定的部分（如年、月）。
    * `EXTRACT(YEAR FROM HIREDATE)` 
* **`LAST_DAY`**: 返回指定日期所在月份的最后一天。
    * `HIREDATE = LAST_DAY(HIREDATE)` 
* **`MONTHS_BETWEEN`**: 计算两个日期之间的月数差。
    * `MONTHS_BETWEEN(CURRENT_DATE, HIREDATE)` 
* **`TRUNC`**: 用于截断日期（去除时间部分）或数值。
    * `TRUNC(CURRENT_DATE)` 

**字符串处理函数：**
* **`SUBSTR`**: 用于截取字符串的子串。
    * `SUBSTR(JOB, 1, 5)` (截取工作名称的前5个字符) 
* **`INITCAP`**: 将字符串的第一个字母转换为大写，其余小写。
    * `INITCAP(ENAME)` 

**数值与聚合函数：**
* **`ROUND`**: 用于对数值进行四舍五入。
    * `ROUND(AVG(SAL), 2)` (保留两位小数)
* **`RANK() OVER`**: 窗口函数，用于对结果集进行排名。
    * `RANK() OVER (ORDER BY e.SAL DESC)` 或 `RANK() OVER (PARTITION BY ...)` 
* **`AVG`, `MAX`, `MIN`, `SUM`, `COUNT`**: 标准聚合函数，在多个实验中用于统计。

**空值处理与序列函数：**
* **`NVL`**: 用于处理空值，如果值为NULL则替换为指定值（常用于计算年薪时处理奖金）。
    * `SAL * 12 + NVL(COMM, 0)` 
* **`NEXTVAL`**: 用于获取序列的下一个值。
    * `SeqDeptNo.NEXTVAL` 

### 2. SQL查询的“坑”点与注意事项

* **大小写敏感性**：Oracle中表名和列名在内部默认是大写的（不区分大小写），但**字符串常量**（即数据内容）是严格区分大小写的。
    * 使用 `UPPER()` 或 `INITCAP()` 函数处理字段后再比较，例如 `WHERE INITCAP(city) = 'Beijing'`。
* **列名模棱两可（Ambiguity）**：在多表连接时，如果两个表有同名列（如 `DEPTNO`），必须加表名前缀或别名。
    *  `SELECT DEPTNO` 会报错，必须写成 `SELECT EMP.DEPTNO。
* **自身连接（Self-Join）的别名**：当一个表和自己连接时（例如查询员工及其经理），**必须**为表指定两个不同的别名（如 `E1` 和 `E2`），否则数据库无法区分。
* **外连接的写法**：
    * *Oracle特有写法*: 使用 `(+)` 符号放在**信息缺失**的一方（即如果不匹配则补NULL的一方）。例如左外连接中，`(+)` 放在右表的列旁。
    * 使用 `LEFT JOIN` / `RIGHT JOIN`。
* **WHERE 与 HAVING 的区别**：
    * 在 `WHERE` 子句中使用聚合函数（如 `WHERE AVG(SAL) > 2000`）是错误的。
    * `WHERE` 用于在分组**前**筛选行；`HAVING` 用于在分组**后**筛选组（可以使用聚合函数）。
* **聚合列的限制**：在使用 `GROUP BY` 时，SELECT 列表中出现的非聚合列，必须全部包含在 `GROUP BY` 子句中，否则会报错。
* **视图的不可更新性**：并非所有视图都可以进行 `INSERT/UPDATE`。如果视图包含了聚合函数（SUM, AVG）、DISTINCT、GROUP BY 或集合操作符（UNION），则该视图通常是**只读**的，不能更新。
* **WITH CHECK OPTION**：如果视图创建时带有此选项，通过视图插入或修改数据时，必须满足视图定义的 `WHERE` 条件，否则操作会被拒绝。
* **列的增删改**：在表中增加、删除或修改多个列时，语法略有不同。例如添加多列需用括号括起来 `ADD (col1 type, col2 type)` 。
* **EXISTS 与 IN 的区别**：
    * `EXISTS` 只判断是否存在，找到第一条匹配记录就停止并返回 TRUE，通常用于相关子查询。
    * `IN` 会建立结果集进行匹配。在处理大量数据或涉及 NULL 值时，两者的行为和性能可能有区别。

---

> 原题练习[[2022SQL查询]]

