
// how to use the table_calc addon:
//
// - include the formula_parser.js file
// - add the following js after the table you want to use

// ---8<------------------------------------------
window.addEventListener('load', function(event) {
    console.log('All resources finished loading!');
    init();
});

var getValue = undefined;
var myFormulaTable = undefined;

function init() {
    console.group('init for test_findNearestInTree...');

    // test for siblings
    console.group('findNearest(*#test_siblings*, \'div.find-me\')');
    let test_siblings = document.querySelector('#test_siblings');
    let test_siblings_result = findNearestInTree(test_siblings, 'div.find-me');
    console.log('!! result:', test_siblings_result);
    test_siblings.addEventListener('mouseover',
        () => test_siblings_result.classList.add('highlight'));
    test_siblings.addEventListener('mouseleave',
        () => test_siblings_result.classList.remove('highlight'));
    console.groupEnd();

    // test for children
    console.group('findNearestInTree(*#test_children*, \'div.find-me\')');
    let test_children = document.querySelector('#test_children');
    let test_children_result = findNearestInTree(test_children, 'div.find-me');
    console.log('!! result:', test_children_result);
    test_children.addEventListener('mouseover',
        () => test_children_result.classList.add('highlight'));
    test_children.addEventListener('mouseleave',
        () => test_children_result.classList.remove('highlight'));
    console.groupEnd();

    // test for parents
    console.group('findNearestInTree(*#test_parents*, \'div.find-me\')');
    let test_parents = document.querySelector('#test_parents');
    let test_parents_result = findNearestInTree(test_parents, 'div.find-me');
    console.log('!! result:', test_parents_result);
    test_parents.addEventListener('mouseover',
        () => test_parents_result.classList.add('highlight'));
    test_parents.addEventListener('mouseleave',
        () => test_parents_result.classList.remove('highlight'));
    console.groupEnd();


    console.groupEnd();
}
// ---8<------------------------------------------
