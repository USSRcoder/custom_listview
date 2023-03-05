# Owner draw ListView (SysListView, ListTreeView, TreeListView)

<pre>

Looks like always expanded SysTreeView, with columns.
Standart SysListView used, with custom owner draw procedure.
Used .iIndent value of item structure, for spacing rows;
Used "original" TREEVIEW_DrawItemLines from comctrl32.dll (see wine),
for drawing tree structure (Lines).
Colored text draw for first colunm.

</pre>

<img src="https://raw.githubusercontent.com/USSRcoder/custom_listview/master/thumb.png">
