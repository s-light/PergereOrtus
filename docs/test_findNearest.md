# Test findNearest
<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->
<!--lint disable code-block-style-->

find nearest
<script src="{{ '/assets/js/table_calc_example.js?v=' | append: site.github.build_revision | relative_url }}" charset="utf-8"></script>

<!-- test case for siblings -->
### world

ein text...

| relative near  | Header Two     |
| :------------- | :------------- |
| same level     | Item Two       |


<!-- test case for parent traversal -->
<section>
    <section id="test-children" >
        <h6>test-children</h6>
        <section>
            <table>
                <tbody>
                    <tr>
                        <td style="text-align: left">one sub level more</td>
                        <td style="text-align: left">Item Two</td>
                    </tr>
                </tbody>
            </table>
        </section>

        <p> - </p>

        <table>
            <tbody>
                <tr>
                    <td style="text-align: left">one sub level more</td>
                    <td style="text-align: left">Item Two</td>
                </tr>
            </tbody>
        </table>
    </section>
</section>

<section>
    <table>
        <tbody>
            <tr>
                <td style="text-align: left">one sub level</td>
                <td style="text-align: left">Item Two</td>
            </tr>
        </tbody>
    </table>
</section>

<!-- test case for parent traversal -->
<section>
    <section>
        <h5 id="test-parent">test-parent</h5>
    </section>
</section>

<section>
    <table>
        <tbody>
            <tr>
                <td style="text-align: left">one sub level</td>
                <td style="text-align: left">Item Two</td>
            </tr>
        </tbody>
    </table>
</section>

## more bla bla
bla bla bla
