# 房屋推薦 (house)

## 問題描述

房屋仲介小潮負責高談市的租房業務。
小潮手上有編號為 $1, 2, \cdots, n$ 的 $n$ 間待租的房屋，
房屋 $i$ 的位置可以用二維座標 $(a_i, b_i)$ 表示，並且此房屋的月租金為 $r_i$ 元。

高談市有 $m$ 座捷運站，
捷運站的編號為 $1, 2, \cdots, m$，
捷運站 $j$ 的位置在二維平面以座標 $(c_j, d_j)$ 表示。
定義房屋 $i$ 與捷運站 $j$ 的距離為 $\sqrt{(a_i - c_j)^2 + (b_i - d_j)^2}$ 單位。

小潮發現租客的喜好如下：

1. 房屋與最近的捷運站的距離越短越好。
2. 如果兩間房屋和彼此最近的捷運站距離一樣近，月租金越小的房屋越好。
3. 如果兩間房屋和彼此最近的捷運站距離一樣近，而且月租金相同，房屋編號越小的越好。

請幫忙小潮開發一個房屋推薦系統，對房屋們進行排序，使得越是得到租客喜愛的房屋排在越前面。

如下圖為一 $n=3$ 且 $m=3$ 的例子，
其中正方形的點 $H_1, H_2, H_3$ 分別代表房屋 $1, 2, 3$，
圓點 $S_1, S_2, S_3$ 則分別代表捷運站 $1, 2, 3$ 的位置。並且：

- 第 $1$ 間房屋位在 $(2, 0)$，月租金為 $11000$ 元。
- 第 $2$ 間房屋位在 $(5, 0)$，月租金為 $12000$ 元。
- 第 $3$ 間房屋位在 $(3, 3)$，月租金為 $10000$ 元。
- 第 $1$ 座捷運站位在 $(1, 3)$。
- 第 $2$ 座捷運站位在 $(3, 0)$。
- 第 $3$ 座捷運站位在 $(5, 3)$。

\begin{figure}[h]
\centering
\begin{tikzpicture}[scale=0.8]
  \draw[help lines, color=gray!30, dashed] (0, 0) grid (6, 6);
  \draw[->,ultra thick] (0,0)--(6,0) node[right]{$x$};
  \draw[->,ultra thick] (0,0)--(0,6) node[above]{$y$};

  \filldraw[red] ([xshift=-2pt,yshift=-2pt]2, 0) rectangle ++(4pt,4pt) node[anchor=north east]{\small$H_1$};
  \filldraw[red] ([xshift=-2pt,yshift=-2pt]5, 0) rectangle ++(4pt,4pt) node[anchor=north west]{\small$H_2$};
  \filldraw[red] ([xshift=-2pt,yshift=-2pt]3, 3) rectangle ++(4pt,4pt) node[anchor=north west]{\small$H_3$};

  \filldraw[black] (1, 3) circle (2.5pt) node[anchor=north west]{\small $S_1$};
  \filldraw[black] (3, 0) circle (2.5pt) node[anchor=north west]{\small $S_2$};
  \filldraw[black] (5, 3) circle (2.5pt) node[anchor=north west]{\small $S_3$};
\end{tikzpicture}
\end{figure}

\newpage

可以算出：

- 和第 $1$ 間房屋距離最短的捷運站為第 $2$ 座捷運站，距離為 $1$ 單位。
- 和第 $2$ 間房屋距離最短的捷運站為第 $2$ 座捷運站，距離為 $2$ 單位。
- 和第 $3$ 間房屋距離最短的捷運站為第 $1$ 座捷運站與第 $3$ 座捷運站，距離為 $2$ 單位。

第 $2$ 間房屋和第 $3$ 間房屋和捷運站的距離都是 $2$ 單位，
但是因為第 $3$ 間房屋的月租金較為便宜，所以排在第 $2$ 間房屋前面。
因此租客喜好的房屋順序為：$1, 3, 2$。

## 輸入格式

\begin{format}
\f{
$n$ $m$
$a_1$ $b_1$ $r_1$
$a_2$ $b_2$ $r_2$
$\vdots$
$a_n$ $b_n$ $r_n$
$c_1$ $d_1$
$c_2$ $d_2$
$\vdots$
$c_m$ $d_m$
}
\end{format}

* $n$, $m$ 分別代表房屋與捷運站的數量。
* 房屋 $i$ 的座標在 $(a_i, b_i)$，且租金為 $r_i$。
* 捷運站 $j$ 的座標為 $(c_j, d_j)$。

## 輸出格式

\begin{format}
\f{
$p_1$
$p_2$
$\vdots$
$p_n$
}
\end{format}

* $p_i$ 為一整數，代表排名第 $i$ 名的房屋編號。

## 測資限制

* $1 \le n \le 10^5$。
* $1 \le m \le 10^3$。
* $-10^9 \le a_i, b_i, c_i, d_i \le 10^9$。
* $0 \le r_i \le 10^9$
* 上述變數皆為整數。
* 任意一個座標最多只有一間房屋或一座捷運站，且不會有房屋和捷運站在同一座標。

## 範例測試

## 評分說明

本題共有三組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | {{score.subtask1}} | $n \le 2$ |
| 2 | {{score.subtask2}} | $n \le 100$ |
| 3 | {{score.subtask3}} | 無額外限制 |
