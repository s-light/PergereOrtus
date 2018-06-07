# Test findNearest
<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->
<!--lint disable code-block-style-->

<script src="{{ '/assets/js/test_findNearest.js?v=' | append: site.github.build_revision | relative_url }}" charset="utf-8"></script>

<style media="screen">
    .find-me {
        border-radius: 0.5em;
        background-color: rgba(0, 255, 255, 0.03);
        transition-property: background-color;
        transition-duration: 1s;
    }
    .highlight {
        background-color: rgba(255, 255, 0, 0.7);
        transition-property: background-color;
        transition-duration: 0.5s;
    }

    .section {
        border-radius: 0.5em;
    }
    .section:hover {
        background-color: rgba(0, 0, 255, 0.2);
    }
</style>

## test siblings
<div class="find-me"> :-) </div>

<button type="button" name="test_siblings" id="test_siblings">try me :-)</button>

<div class="find-me"> :-) </div>

## test children
<section>
    <button type="button" name="test_children" id="test_children">try me :-)</button>
    <section>
        <div class="find-me"> :-) </div>
        <section>
            <div class="find-me"> :-) </div>
        </section>
        <div class="find-me"> :-) </div>
    </section>
    <div class="find-me"> :-) </div>
</section>

## test parents
<section>
    <div class="find-me"> :-) </div>
</section>
<section>
    <section>
        <button type="button" name="test_parents" id="test_parents">try me :-)</button>
    </section>
</section>
<div class="find-me"> :-) </div>

## more bla bla
bla bla bla
