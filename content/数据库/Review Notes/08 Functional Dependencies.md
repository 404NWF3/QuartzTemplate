## 重点

- 3. 闭包与阿姆斯特朗公理 (Closure & Armstrong’s Axioms)
- 4. 属性集的闭包 (Closure of a Set of Attributes)
- 6. 不可约依赖集 / 最小覆盖 (Irreducible Sets / Minimal Cover)

## 1. 基础定义 (Basic Definitions)

### 1.1 什么是函数依赖？

**定义：** 设 $R$ 是一个关系变量，X 和 Y 是 $R$ 的属性子集。当且仅当在 $R$ 的每一个可能的合法值（关系实例）中，每一个 X 值都精确地对应一个 Y 值时，称 **Y 函数依赖于 X**（Y is functionally dependent on X），记作：
$$X \to Y$$
*   **读作：** "X 函数决定 Y" (X functionally determines Y) 或 "X 箭头 Y" (X arrow Y)。
*   **实质：** 如果两个元组在 X 属性上的值相同，那么它们在 Y 属性上的值也必须相同。
*   **示例：** 在发货记录中，$\{S\#, P\#\} \to \{QTY\}$ 表示特定的供应商和零件组合决定了唯一的数量。

### 1.2 函数依赖的用途 (Use of FDs)

1.  **约束检查 (Specify Constraints):** 用于定义关系中哪些数据是合法的。若所有合法关系都满足某组依赖 S，则称 S 在 R 上成立 (Holds on R)。
2.  **DBMS 优化:** 实际应用中存在的函数依赖非常多，DBMS 需要找到一个较小的依赖集（Cover），只要检查这个小集合就能保证所有依赖都满足。

---
## 2. 依赖的分类 (Classification of Dependencies)

### 2.1 平凡依赖 (Trivial Dependencies)

*   **定义：** 如果右边（RHS）是左边（LHS）的子集，则该函数依赖是平凡的。
*   **公式：** 如果 $Y \subseteq X$，则 $X \to Y$ 是平凡的。
*   **特点：** 这种依赖永远成立，但在实际应用中意义不大（Not very interesting in practice）。
*   **示例：** $\{S\#, P\#\} \to \{S\#\}$。

### 2.2 非平凡依赖 (Nontrivial Dependencies)

*   即右边不是左边子集的依赖，这是数据库设计主要关注的对象。

---
## 3. 闭包与阿姆斯特朗公理 (Closure & Armstrong’s Axioms)

### 3.1 依赖集的闭包 (Closure of a Set of Dependencies, $S^+$)

给定一组函数依赖 S，由 S 所能**推导出**的所有函数依赖的集合，称为 S 的闭包，记为 $S^+$。

### 3.2 阿姆斯特朗公理 (Armstrong’s Axioms)

这是一组推理规则，用于推导闭包。它们是**完备的 (Complete)** 和 **有效的 (Sound)**。

1.  **自反律 (Reflexivity):** 若 $B \subseteq A$，则 $A \to B$（即平凡依赖）。
2.  **增广律 (Augmentation):** 若 $A \to B$，则 $AC \to BC$。
3.  **传递律 (Transitivity):** 若 $A \to B$ 且 $B \to C$，则 $A \to C$。

### 3.3 导出规则 (Derived Rules)

为了简化推导，可以从上述三条公理导出以下规则：

*   **自决律 (Self-determination):** $A \to A$。
*   **分解律 (Decomposition):** 若 $A \to BC$，则 $A \to B$ 且 $A \to C$。
*   **合并律 (Union):** 若 $A \to B$ 且 $A \to C$，则 $A \to BC$。
*   **复合律 (Composition):** 若 $A \to B$ 且 $C \to D$，则 $AC \to BD$。

---
## 4. 属性集的闭包 (Closure of a Set of Attributes)

### 4.1 定义与用途

*   **定义：** 给定属性集 Z 和依赖集 S，Z 的闭包 $Z^+$ 是指所有被 Z 函数决定的属性的集合。
*   **用途：** 
    1.  **验证依赖：** $X \to Y$ 成立，当且仅当 $Y \subseteq X^+$。
    2.  **识别超码 (Superkey):** K 是超码，当且仅当 $K^+$ 包含关系中的所有属性。

### 4.2 计算算法 (Algorithm)

1.  初始化结果集 `CLOSURE` 为 $Z$。
2.  反复遍历所有函数依赖 $X \to Y$。
3.  如果 $X$ 包含在当前的 `CLOSURE` 中，则将 $Y$ 加入 `CLOSURE`。
4.  重复步骤，直到结果集不再增大为止。

---
## 5. 覆盖与等价 (Cover and Equivalent)

*   **覆盖 (Cover):** 如果依赖集 $S_1$ 蕴含的所有依赖都能由 $S_2$ 推导出来（即 $S_1^+ \subseteq S_2^+$），则称 $S_2$ 是 $S_1$ 的覆盖。
    *   *意义：* 如果 DBMS 强制执行了 $S_2$，则自动强制执行了 $S_1$。
*   **等价 (Equivalent):** 如果 $S_1$ 是 $S_2$ 的覆盖，且 $S_2$ 也是 $S_1$ 的覆盖（即 $S_1^+ = S_2^+$），则称两者等价。

---
## 6. 不可约依赖集 / 最小覆盖 (Irreducible Sets / Minimal Cover)

### 6.1 定义

一个函数依赖集 S 是不可约的（Irreducible），当且仅当它满足以下三个条件：
1.  **右边由单属性组成 (Singleton RHS):** 每个 FD 的右边只包含一个属性。
2.  **左边不可约 (LHS Irreducible):** 左边没有任何多余的属性。如果去掉左边的某个属性，闭包会发生改变。
3.  **无多余依赖 (No Redundant FDs):** 集合中没有任何多余的 FD。如果去掉某条依赖，闭包会发生改变。

### 6.2 寻找不可约集的步骤 (Algorithm)

对于任意依赖集 S，都存在一个与之等价的不可约集 I。计算步骤如下：
1.  **右边单属性化：** 将 $A \to BC$ 拆解为 $A \to B$ 和 $A \to C$。
2.  **左边最小化：** 对每个 FD，检查左边的属性是否冗余。
    *   *方法：* 例如 $AB \to C$，检查是否 $A \to C$ 或 $B \to C$ 已经可以通过其他依赖推导出来。
3.  **消除多余依赖：** 检查某条 FD 是否可以被集合中剩余的 FD 推导出来。
    *   *方法：* 暂时去掉某条 FD，计算左边属性在剩余集合下的闭包，看是否包含右边属性。

---
[[关系数据理论 习题]]