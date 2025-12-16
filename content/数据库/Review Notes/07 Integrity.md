## 重点

- 2. 约束的分类 (Classification Scheme)
- 4. 静态与动态约束 (State vs. Transition Constraints)
- 5. 键 (Keys)

## 1. 什么是完整性？

*   **完整性 (Integrity):** 指数据库中数据的**准确性 (Accuracy)** 或 **正确性 (Correctness)**。
*   **完整性检查机制:** 当声明了一个新约束时，系统首先检查现有数据是否满足该约束。如果不满足，新约束被拒绝；如果满足，系统将在后续操作中强制执行该约束，**拒绝**任何违反约束的更新操作。

---
## 2. 约束的分类 (Classification Scheme)

> 2022DB 填空题 

根据约束作用的范围，将其分为四个层次：

### 2.1 类型约束 (Type Constraints)

*   **定义:** 指定给定**类型 (Type/Domain)** 的合法值集合。它是最基本的约束形式。
*   **示例:** 定义颜色域只能包含 'RED', 'YELLOW', 'GREEN'；或者定义时薪域必须大于 4.00。
*   **检查时机:** **立即检查 (Checked immediately)**。任何关系变量的属性都不能获得不属于该类型的值。

### 2.2 属性约束 (Attribute Constraints)

*   **定义:** 声明某个特定**属性 (Attribute)** 属于某个特定的类型。
*   **内容:** 包括 `NOT NULL` 约束以及特定于该列的 `CHECK` 条件。
*   **检查时机:** **立即检查**。

### 2.3 关系变量约束 (Relvar Constraints)

*   **定义:** 针对单个**关系变量 (Relvar/Table)** 的约束。
*   **示例:** 规定“位于伦敦的供应商状态值必须为 20。
*   **检查时机:** **立即检查**。任何违反该约束的赋值语句（Insert/Update）都会被拒绝。

### 2.4 数据库约束 (Database Constraints)

*   **定义:** 涉及两个或更多不同关系变量之间相互关系的约束。
*   **示例:** “状态值小于 20 的供应商不能供应数量大于 500 的零件” (涉及 S 和 SP 两个表)。
*   **检查时机:** 通常**推迟 (Deferred)** 到事务结束 (End-of-Transaction / COMMIT) 时检查。如果在提交时违背约束，事务将回滚。

---
## 3. 黄金法则 (The Golden Rule)

*   **谓词 (Predicate):** 每个关系变量都有一个相关的谓词（逻辑条件），即所有适用于该关系变量的约束的逻辑“与” (AND)。
*   **法则内容:**
    1.  绝不允许任何更新操作使任何**关系变量**处于违反其自身谓词的状态。
    2.  绝不允许任何更新事务使**数据库**处于违反其自身谓词的状态。

---
## 4. 静态与动态约束 (State vs. Transition Constraints)

*   **静态约束 (State Constraints):** 关注数据库的**正确状态**（即只要当前值合法即可，不关心它之前是什么）。
*   **动态/转换约束 (Transition Constraints):** 关注从一个正确状态到另一个正确状态的**合法转换**。
    *   **示例:** 婚姻状况可以从“未婚”变为“已婚”，但不能从“未婚”直接变为“丧偶”；或者“工资只能涨不能跌”。

---
## 5. 键 (Keys)

### 5.1 候选键 (Candidate Keys

一个属性集 K 是关系变量 R 的候选键，当且仅当它满足以下两个性质：

1.  **唯一性 (Uniqueness):** R 中不存在两个不同的元组在 K 上具有相同的值。
2.  **不可约性 (Irreducibility):** K 的任何真子集都不具备唯一性。

### 5.2 主键与备用键 (Primary & Alternate Keys)

*   **主键 (Primary Key):** 从候选键中被选定作为主要标识符的那个键。
*   **备用键 (Alternate Keys):** 未被选为主键的其他候选键。

### 5.3 外键 (Foreign Keys)

*   **定义:** 关系 R2 中的一组属性 FK，其值必须与关系 R1（R1 和 R2 可以相同）中某个元组的**候选键 CK** 的值相同。
*   **目的:** 确保参照完整性 (Referential Integrity)。

---
## 6. 参照完整性动作 (Referential Actions)

当删除或更新被引用的数据（主表数据）时，为了维护外键约束，系统采取的策略：

*   **CASCADE (级联):** 主表删除/更新，从表对应的记录也自动删除/更新。
*   **RESTRICT / NO ACTION (受限):** 如果从表有引用，则禁止主表执行删除/更新操作。
*   **SET NULL (置空):** 主表删除/更新，从表对应的外键值设为 NULL。
*   **SET DEFAULT (置缺省):** 主表删除/更新，从表对应的外键值设为默认值。

---
## 7. 触发器与断言 (Triggers & Assertions)

### 7.1 触发器 (Triggers)

*   **定义:** 当数据库发生修改（如 INSERT, UPDATE, DELETE）时，由系统自动执行的一段语句（副作用）。
*   **组成:** 事件 (Event)、条件 (Condition)、动作 (Action)。
*   **用途:** 实现复杂的完整性规则、审计日志、自动级联更新等（例如：当账户余额透支时，自动创建一笔贷款并置余额为0）。

### 7.2 断言 (Assertions)

*   **定义:** 一个希望数据库**始终**满足的谓词表达式。
*   **SQL 语法:** `CREATE ASSERTION <name> CHECK <predicate>`。
*   **特点:** 不依附于单个表，是全局约束。但由于检查开销大，需谨慎使用。

### 7.3 约束的延迟 (Deferrable Constraints)

*   **NOT DEFERRABLE:** 始终立即检查。
*   **DEFERRABLE:** 可以通过 `SET CONSTRAINTS ... DEFERRED` 暂时关闭检查，直到事务提交 (COMMIT) 时强制检查。
