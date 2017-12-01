## 1.引论
#### 1.1 概念 comception of compiler
- compiler 阅读某一种语言(source language)编写的程序，并翻译成 **等价的** 目标语言(target language)编写的程序
- comparison between compiler and interpreter<p>
速度 compiler > interpreter，错误诊断 interpreter > compliler

#### 1.2 编译的阶段(Phases)
- front end->分析(analysis)：分成多个要素，生成源程序的中间表示（intermediate representation）<p>
  只依赖源程序，独立于目标机器
- back end->综合(synthesis)：中间表示转换为目标代码<p>
  依赖于目标机器，与中间程序有关，源程序无关
- advantage: 前后端分离可提升效率

#### 1.3 框架 framwork of compiler

            前端(front end)
    -词法分析(Lexical Analysis/scanning)
      源程序字符序列  → 单词符号序列
    -语法分析（Syntax Analysis）
      单词符号序列  →  分析树（Parse/Syntax Tree）
      f: 层次分析 hierarchical Analysis
    -语义分析（Semantic Analysis）
      分析树   →   带语义（注释）的树
      f: 类型检查和转换 type checking & coercion
    -中间代码生成（Intermediate Code Generation）
      带语义（注释）的树  → 中间代码 /three-address code
      ------------------------
            后端(back end)
    -代码优化（Code Optimization）
      提高时间与空间效率
    -目标代码生成（Code Generation）
      为变量分配寄存器，中间语言指令->合适的机器指令序列

- other phases<p>
符号表管理(Symbol-Table Management): 管理源程序中的标识符的各种信息<p>
出错处理(Error Detection and Reporting): 检查错误位置、性质并修复

## 2.文法和语言
#### 2.1串和语言(string & languale)
- 字母表(alphabet)：符号(symbols)的非空有穷集合,用∑表示
- 符号串/字(string):字母表中的符号所组成有穷序列，长度记为|s|
  - 空符号串ε， |ε|=0
  - 前缀(prefix)：移走符号串s尾部的零个或多于个符号得到的串
  - 后缀(suffix)：删去符号串s头部的零个或多于个符号得到的串
  - 子串(substring)：从s中删去一个前缀和后得到的符号串
  - 运算：连接、方幂
- 语言(language)：某个字母表上的符号串集合
  - 运算：并、交、差、连接(x)、* 闭包($L^* =L_0∪L_1∪L_2∪L_3∪…$)、+闭包($L^+=L_1∪L_2∪L_3∪…$)

#### 2.2文法/语言的定义(definition)
- 文法(Grammar)定义*：语言中的每个句子可以用严格定义的规则来构造($V_T,V_N,S,P$)
  - $V_T$:终结符(terminals),元素一般用小写字母或数字表示,代表语言中不可再分的基本符号.$V_T= [a,b,c,…x,y,z,0,1,…,9]$
  - $V_N$:非终结符(nonterminals),元素一般用大写字母表示,或者用尖括号括起,代表语法单位.$V_N= [<标识符>，<字母>，<数字>]$
  - S：开始符号(start symbol),特殊的非终结符号.S = < 标识符 >
  - P：产生式（production）的集合，形如α→β
- 推导(derivation)/归约(reduction):
  - 推导是用产生式的右部代替左部,归约是用产生式的左部代替右部,归约是推导的逆过程
  - 最左/右推导:对α中的最左/右非终结符进行展开
  - 最左/右归约:左/右推导的逆过程，最左归约称为规范归约
- 句型/句子(sentential form/sentence)
  - 句型：从文法的开始符号出发进行零步或多于零步的推导得到的文法符号串,可以既包含终结符号又包含非终结符号。
  - 句子是一种特殊的句型，只包含终结符号
- 语言(language)定义：文法推导出的所有句子组成集合，称为语言，记为L(G)
- 等价文法(equivalent)：语言和文法时一对多的关系，文法之间等价

#### 2.3分类(classification)*
- 0型：$α→β(α\neqε)$
- 1型(上下文有关)：$α→β(|α| ≤ |β|)$
- 2型(上下文无关)：$A→β(A ∈ V_N，β ∈(V_T∪V_N)^* )$
- 3型(正规)：A→a & A→aB(右线性) & A→Ba(左线性)
- 四种文法/语言之间逐级包含关系
#### 2.4分析树和句型(parse tree & sentential form)
- 分析树：描述上下文无关法句型推导的一种直观方法，也称为推导树。
  - 特性：根标识为开始符号，内部结点标识为非终结符号，产生式左右排列
- 句型
  - 短语：
  - 直接短语：
  - 句柄：
  - 素短语：
  - 最左素短语：
- 二义性：

## 3.词法分析
#### 3.1词法分析器的作用(The role of the lexical analysis)
- 读入源程序字符序列——>对源程序进行预处理——>识别源程序中的单词符号，创建符号表——>将符号表和行号关联——>输出单词符号序列
- 单词符号：关键字，运算符，标识符，常数，字符串，标点符号
- 输出二元式：<单词符号种类，属性值>

#### 3.2单词符号的描述(Specification of tokens)
- 正规表达式( Regular Expression )：表示字符串格式的模式，采用递归定义
- 关键字：begin|end|if|while…
- 运算符：| × + -
- 标识符：Letter=A|B|…|a|b|…/Digit=0|1|2|…/Id=Letter(Letter|Digit)*
- 常数：(digit)=digit(digit)* /(digit)+(.(digit)+|ε)((E(+|-|ε)(digit)+)|ε)
- 标点：,|;|:|…

#### 3.3有限自动机(Finite automata)*
- 非确定的有限自动机(NFA)($S,Σ,move,S_0,F$五元组):
  - $S$ — 状态集合
  - $Σ$ — 输入符号集合
  - $move$ — 转换函数(S×Σ → S)
  - $S_0$— 开始状态
  - $F$ — 接受状态集合
- 确定的有限自动机(DFA)：没有ε边转移,一个状态面临一个输入符号时最多只转移到一个状态
  - 表示方法：状态转换图(transition graph)/状态转换表(transition table) ##见书本
- NFA-DFA转换：子集构造法(subset construction)* ：
    - $ε-closure(s)$(状态s的ε-闭包):定义为一个状态集合,是状态s经过任意条ε边到达的状态所组成的集合
    - $ε-closure(T)$(状态集合T的ε-闭包):定义为一个状态集合,是状态集合 T 中的任何状态经过任意条ε边到达的状态集合
    - $Move(T,a)$(状态集合T的a边转换):定义为一个状态集合,是状态集合T中的任何状态经过a边到达的状态
- 正规表达式构造 NFA ##见书本
- DFA化简：为DFA寻找一个状态数比较少的等价DFA
  - 求同法：寻找等价状态,合并之
  - 求异法：首先将状态划分为接受状态与非接受状态两组,然后逐步将这个划分精细化,最后得到一个不可再细化的状态集的划分,每个状态子集作为一个状态 (p142-143)

- 正规表达式直接构造 DFA (p135) ε,a,s|t,st，s*，(s)的展开
- ####词法分析步骤：处理源程序——>构建单词符号表——>正则表达式——>NFA——>DFA——>DFA化简

## 4.语法分析
#### 4.1 自顶向下的分析
- 不确定的自顶向下分析
- 确定的自顶向下分析
- FIRST集：
- FOLLOW集：
- SELECT集：
- LL(1)文法
  - 提取左因子
  - 消除左递归
    - 直接左递归
    - 间接左递归
    - 构造预测分析表
    - 预测分析算法

#### 4.2 自底向上的分析
#### 4.3 算符优先分析
#### 4.4 LR分析
