## 重点

- 2. Codd 的八大操作 (Codd’s Original Eight Operators)

---
## 1. 核心概念与特性 (Core Concepts & Properties)

### 1.1 定义 (Definition)

关系代数基本上是一组**操作符 (Operators)** 的集合。

*   **输入 (Operands):** 一个或多个关系（Relation）。
*   **输出 (Result):** 一个新的关系。

### 1.2 闭包性质 (Closure Property)

*   **定义:** 任何关系运算的输出结果仍然是一个**关系 (Relation)**（即表）。
*   **意义:** 这使得我们可以编写**嵌套的关系表达式 (Nested relational expressions)**，即一个运算的输出可以作为另一个运算的输入。

---
## 2. Codd 的八大操作 (Codd’s Original Eight Operators)

### 2.1 传统集合操作 (Traditional Set Operators)

1.  **并运算 (Union):** $A \cup B$
    *   **定义:** 结果包含属于 A **或者** 属于 B **或者** 同时属于两者的所有元组。
    *   **逻辑:** OR (逻辑或)。
2.  **交运算 (Intersection):** $A \cap B$
    *   **定义:** 结果包含既属于 A **又** 属于 B 的所有元组。
    *   **逻辑:** AND (逻辑与)。
3.  **差运算 (Difference):** $A - B$ (或 $A \text{ MINUS } B$)
    *   **定义:** 结果包含属于 A **但不属于** B 的元组。
    *   **注意:** 顺序很重要，$A - B$ 不等于 $B - A$。
4.  **笛卡尔积 (Cartesian Product):** $A \times B$ (或 $A \text{ TIMES } B$)
    *   **定义:** 结果包含 A 中每个元组与 B 中每个元组的拼接（Coalescing）。
    *   **规模:** 结果的基数（行数）是 A 和 B 基数的乘积；度（列数）是 A 和 B 度之和。
    *   **特点:** 不需要两个关系具有公共属性；虽然在理论上重要，但由于产生数据量巨大，在实际应用中很少单独使用，通常配合选择运算使用。

### 2.2 专门的关系操作 (Special Relational Operators)

1.  **选择/限制 (Restrict / Select):** $\sigma$ (Codd写作 $A \text{ WHERE condition}$)
    *   **定义:** **水平分割**。根据指定条件从关系 A 中选取满足条件的元组子集。
    *   **特点:** 结果表的列与原表相同，行数减少。
    *   **条件:** 可以是 $=, \neq, >, \ge$ 等比较，也可以是 AND, OR, NOT 组合的布尔表达式。
2.  **投影 (Project):** $\pi$ (Codd写作 $A \{X, Y, \dots\}$)
    *   **定义:** **垂直分割**。从关系 A 中选取指定的属性列（X, Y...）。
    *   **特点:** 结果表会自动**去除重复的元组**（因为关系是集合，不允许重复）。
3.  **连接 (Join):**(Codd写作 $A$  $JOIN$  $B$)
    *   **自然连接 (Natural Join):** 基于两个关系中名称相同的公共属性进行连接。结果自动去除重复的公共列。
        *   如果 A 和 B 没有公共属性，自然连接退化为笛卡尔积。
    *   **$\theta$-连接 ($\theta$-Join):** 基于笛卡尔积，再筛选满足特定条件 ($R \theta S$) 的元组。
    *   **等值连接 (Equijoin):** 当 $\theta$ 为“=”时的 $\theta$-连接。
4.  **除运算 (Divide):** $A \div B$ (通常写作 $A \text{ DIVIDEBY } B \text{ PER } C$)
    *   **用途:** 用于处理“查询......**所有 (All)**......”这类问题。
    *   **例子:** 找出供应了**所有**零件的供应商。
    *   **定义:** 结果包含 A 中的属性值 x，使得对于 B 中的每一个 y，在 A 中都存在一个元组 (x, y)。

---
## 3. 重要性质与基本集 (Properties & Primitives)

### 3.1 结合律与交换律 (Associativity and Commutativity)

*   **适用:** 并 (Union)、交 (Intersection)、自然连接 (Join)、笛卡尔积 (Product)。
    *   例如：$A \text{ JOIN } B = B \text{ JOIN } A$ (交换律),。
    *   例如：$(A \cup B) \cup C = A \cup (B \cup C)$ (结合律)。
*   **不适用:** 差运算 (Difference) 既不满足交换律也不满足结合律。

### 3.2 最小完备集 (Minimal Set / Primitives)

Codd 的八个操作中，有些是可以由其他操作推导出来的。**最小的基本操作集**包含以下 5 个：
1.  **Restrict (选择)**
2.  **Project (投影)**
3.  **Product (笛卡尔积)**
4.  **Union (并)**
5.  **Difference (差)**

> Join (连接)、Intersection (交) 和 Divide (除) 都可以由上述 5 个基本操作组合而成

[[2022关系代数大题]]
