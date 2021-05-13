
# Table of Contents

1.  [El tercero](#org4a419b5)
    1.  [Supported answers](#org050963f)



<a id="org4a419b5"></a>

# El tercero

This is the project initializer used internally at Robopill,
nothing too amazing, the template files are embedded 
so it can be used in any computer without worry,
everyone is encouraged to fork it 
and modify the template files to their needs
AND it guides you when you run it, so, no real
need for a true readme, just run `etr`!

If you have [Task](https://github.com/go-task/task) installed, just run `task install` otherwise run `go build  -o bin/etr -ldflags="-s -w" src/etr.go` then copy it to somewhere in your `$PATH`

1.  Quick note

    You shouldn't run binaries from the internet, even if it's from an open source project, 
    so I encourage you to
    compile it yourself, anyways, if you still want to run the binaries compiled
    by a stranger you can download:
    [here](https://github.com/hyakuburns/El_Tercero/releases).


<a id="org050963f"></a>

## Supported answers

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">Question</th>
<th scope="col" class="org-left">Valid Answers</th>
<th scope="col" class="org-left">Notes</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">Project name</td>
<td class="org-left"><code>you have to email me and ask me if your project name is ok</code></td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">Language</td>
<td class="org-left"><code>c</code>, <code>cpp</code>, <code>go</code>, <code>rs</code>, <code>zig</code></td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">Build system</td>
<td class="org-left"><code>cmake</code>, <code>meson</code>, <code>premake</code></td>
<td class="org-left">Go defaults to <a href="https://github.com/go-task/task">Task</a></td>
</tr>


<tr>
<td class="org-left">&#xa0;</td>
<td class="org-left">&#xa0;</td>
<td class="org-left">Zig defaults to <code>build.zig</code> files</td>
</tr>


<tr>
<td class="org-left">&#xa0;</td>
<td class="org-left">&#xa0;</td>
<td class="org-left">Rust defaults to <code>cargo</code> since I think 99.9% of people use cargo</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">License</td>
<td class="org-left">For bsd: <code>b</code>, <code>bsd</code></td>
<td class="org-left">&#xa0;</td>
</tr>


<tr>
<td class="org-left">&#xa0;</td>
<td class="org-left">Numbers: <code>1</code>, <code>2</code>, <code>3</code>, <code>4</code></td>
<td class="org-left">&#xa0;</td>
</tr>


<tr>
<td class="org-left">&#xa0;</td>
<td class="org-left">For gpl: <code>g</code>, <code>gpl</code></td>
<td class="org-left">&#xa0;</td>
</tr>


<tr>
<td class="org-left">&#xa0;</td>
<td class="org-left">Numbers: <code>2</code>, <code>2 or later</code>, <code>3, ~3 or later</code></td>
<td class="org-left">&#xa0;</td>
</tr>


<tr>
<td class="org-left">&#xa0;</td>
<td class="org-left">For mit: <code>mit</code></td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">Author</td>
<td class="org-left"><code>Again, you have to email me with your name and before you use it</code></td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">Git or HG?</td>
<td class="org-left"><code>git</code>, <code>hg</code>, <code>both</code></td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>
</table>


### Aditional Notes

-   Sets up clang-format with google style
-   It sets up compile-commands exporting in CMake (meson has it by default and premake can't do that)
-   It sets up rustfmt with sane defaults
-   Sets up ZLS for zig

