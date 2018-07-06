'use strict';
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Helper functions to find nearest element

// TODO
// add variant that searches with visual positions


// inspired by
// https://stackoverflow.com/questions/41826085/find-nearest-element-not-closest/41834199#41834199
function findNearestInTree(start_element, selector) {
    // find nearest element with given selector
    // nearest = search in this order: (first found is returned)
    // - prefer previous siblings first
    // - search in the children
    // - search in the parents
    // repeat recusive

    // ******************************************
    // internal helper functions

    let attribute_name = 'findNearest';
    // let exclude_selector = ':not([' + attribute_name + '=visited])';
    let exclude_selector = ':not([' + attribute_name + '])';

    // function findNearestRecusive(element_list, selector) {
    function findNearestRecusive(target, element, selector) {
        let result = null;
        // let element = element_list[0];

        // console.log('element', element);
        // check siblings
        if (!result) {
            // console.log('checkSiblings');
            result = checkSiblings(target, element, selector);
        }

        // console.log('element', element);
        // check children
        if (!result) {
            // console.log('checkChildren');
            result = checkChildren(target, element, selector);
        }

        // console.log('element', element);
        // mark the current element as visited
        // element.setAttribute(attribute_name, 'visited');

        // console.log('element', element);
        // check parent
        if (!result) {
            // console.log('checkParent');
            result = checkParent(target, element, selector);
        }


        // if (element_list.length > 0) {
        //     for (let element of element_list) {
        //      // result.concat(findNearestRecusive(start_element, selector));
        //
        //
        //     }
        // } else {
        //     // nothing to do.
        //     // we return an empty list.
        // }
        return result;
    }

    function checkSiblings(target, element, selector) {
        //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // check siblings
        // first check if we have any siblings that are relevant
        let nearest_sibling = null;
        if (element) {
            let parentEl = element.parentElement;
            let parentPath = getSelectorFromRoot(parentEl);
            // console.log('parentPath', parentPath);
            let matching_siblings =
                parentEl.querySelectorAll(parentPath + ' > ' + selector);
            let nearest_sibling_distance = 999999;
            // let target_index = findNodeIndex(target);
            let target_index = findNodeIndex(element);
            if (matching_siblings.length > 0) {
                // (element.parentElement.childElementCount > 1)
                for (let child of matching_siblings) {
                    let child_index = findNodeIndex(child);
                    let child_distance = child_index - target_index;
                    //  0 1 2 3 *4 5 6
                    // 2 - 4 = -2
                    // 5 - 4 = 1
                    // 6 - 4 = 2
                    if (
                        (Math.abs(child_distance) < nearest_sibling_distance) ||
                        (
                            (
                                Math.abs(child_distance) ===
                                nearest_sibling_distance
                            ) &&
                            (child_distance < 0)
                        )
                    ) {
                        nearest_sibling_distance = Math.abs(child_distance);
                        nearest_sibling = child;
                    }
                }

            }
        }
        return nearest_sibling;
    }

    function checkChildren(target, element, selector) {
        //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // check children
        let nearest_child = null;
        if (element) {
            // we use a shortcut and hope that the first found is the nearest..
            nearest_child = element.querySelector(selector);

            // TODO
            // change this behavior:
            // check for the nearest element i
            let children = element.children;
            // console.log('children', children);
            // first check if we have any children that are relevant
            let matching_children = element.querySelectorAll(selector);
            // console.log('matching_children', matching_children);
            if (matching_children > 0 && children.length > 0) {
                // calculate distance to target_element
                // compare distances and use nearest.
            }

        }
        return nearest_child;
    }

    function checkParent(target, element, selector) {
        let result = null;
        if (element) {
            let parentEl = element.parentElement;
            // check if we have a valid parent
            // (if not we have reached the root of the tree)
            if (parentEl) {
                // console.group('ping: recusive');
                // console.log('new values: \n',
                //     '  target', target, '\n',
                //     '  new element', parentEl
                //     // '  element', element, '\n',
                //     // '  parentEl', parentEl
                // );
                result = findNearestRecusive(target, parentEl, selector);
                // console.groupEnd();
            }
        }
        return result;
    }

    function cleanup() {
        let all_visited = document.querySelectorAll('[' + attribute_name + ']');
        for (let el of all_visited) {
            el.removeAttribute(attribute_name);
        }
    }



    // ******************************************
    // main function
    let result = null;
    if (start_element) {
        let element_list = document.querySelectorAll(selector);
        // console.log('element_list', element_list);
        if (element_list.length > 0) {
            if (element_list.length == 1) {
                // easy - there is only one match.
                // so we can use it directly..
                result = element_list[0];
            } else {
                // console.log('start_element', start_element);
                result = findNearestRecusive(
                    start_element, start_element, selector);
                // cleanup();
            }
        } else {
            // nothing found.
        }
    } else {
        throw 'now start_element given';
    }
    return result;
}


// inspired by
// https://stackoverflow.com/questions/13656921/fastest-way-to-find-the-index-of-a-child-node-in-parent/13660565#13660565
function findNodeIndex(node) {
    var i = 1;
    while (node = node.previousElementSibling)
        ++i;
    return i;
}


function findNearestOLD(start_element, selector) {
    // find nearest element with given selector
    // prefer children first
    // prefer previous siblings
    let result_element = null;
    let element_list = document.querySelectorAll(selector);
    if (element_list.length > 0) {
        if (element_list.length == 1) {
            // easy - there is only one match.
            // so we can use it directly..
            result_element = element_list[0];
        } else {
            // collect all level-distances
            let level_distances = [];
            for (let el of element_list) {
                level_distances.push(levelStepsBetween(start_element, el));
            }
            console.log('level_distances', level_distances);

            // find smallest level
            let smallest_value = level_distances.slice().sort()[0];
            console.log('smallest_value', smallest_value);

            // collect duplicates
            let smallest_level_indexes = [];
            for (let entry of level_distances.entries()) {
                let index = entry[0];
                let value = entry[1];
                // console.log('index', index, 'value', value);
                // console.log(
                //     'value === smallest_value',
                //     value === smallest_value);
                if (value === smallest_value) {
                    smallest_level_indexes.push(index);
                }
            }
            console.log('smallest_level_indexes', smallest_level_indexes);

            // if we have only one index we are done :-)
            if (smallest_level_indexes.length === 1) {
                result_element = element_list[smallest_levels.index];
            } else {
                // multiple indexes with same levels...
                if (smallest_value === 0) {
                    // we have to check for nearer siblings..
                    // TODO
                } else {
                    // WHAT TO DO NOW???
                    // how to calculate the 'distance' ???
                    // TODO
                }
            }
        }
    } else {
        // nothing found.
    }
    return result_element;
}


function getParentsToRoot(element) {
    // returns a flat array list with all parents up to the root HTML
    let levels = [element];
    let current = element;
    while ((current !== null) && (current.nodeName !== 'HTML')) {
        current = current.parentElement;
        levels.unshift(current);
    }
    return levels;
}

function getSelectorFromRoot(element) {
    // returns a string that can be used as unique CSS Selector
    let levels = [];
    if (element) {
        levels.unshift(element.nodeName);
        let current = element;
        while ((current !== null) && (current.nodeName !== 'HTML')) {
            current = current.parentElement;
            levels.unshift(current.nodeName);
        }
    }
    return levels.join(' > ');
}

// loosely inspired by
// https://stackoverflow.com/a/5350888/574981
function commonAncestor(element1, element2) {
    let result = null;
    let parents1 = getParentsToRoot(element1);
    let parents2 = getParentsToRoot(element2);

    if (parents1[0] === parents2[0]) {
        // sort into long and short parents array
        let short_list = [];
        let long_list = [];
        if (parents1.length > parents2.length) {
            long_list = parents1;
            short_list = parents2;
        } else {
            long_list = parents2;
            short_list = parents1;
        }
        // find last common ancestor
        let i = 0;
        while ((i < short_list.length) && (short_list[i] === long_list[i])) {
            i++;
        }
        let commonAncestorIndex = i - 1;
        let commonAncestor = short_list[commonAncestorIndex];
        result = commonAncestor;
    } else {
        throw 'No common ancestor!';
    }
    return result;
}

function levelStepsBetween(element1, element2) {
    let result = null;
    let parents1 = getParentsToRoot(element1);
    let parents2 = getParentsToRoot(element2);

    if (parents1[0] === parents2[0]) {
        // sort into long and short parents array
        let short_list = [];
        let long_list = [];
        if (parents1.length > parents2.length) {
            long_list = parents1;
            short_list = parents2;
        } else {
            long_list = parents2;
            short_list = parents1;
        }
        // find last common ancestor
        let i = 0;
        while ((i < short_list.length) && (short_list[i] === long_list[i])) {
            i++;
        }
        let commonAncestorIndex = i - 1;
        // let commonAncestor = short_list[commonAncestorIndex];
        // console.log('commonAncestorIndex', commonAncestorIndex);
        // console.log('parents1.length', parents1.length);
        // console.log('parents2.length', parents2.length);
        let distanceElement1ToCommon =
            parents1.length - (commonAncestorIndex + 1);
        let distanceElement2ToCommon =
            parents2.length - (commonAncestorIndex + 1);
        let distance1To2 = 0;
        if (distanceElement1ToCommon === 1 && distanceElement2ToCommon === 1) {

        } else {
            distance1To2 = (
                distanceElement1ToCommon + distanceElement2ToCommon + 1);
        }
        // console.log('distance1To2', distance1To2);
        result = distance1To2;
    } else {
        throw 'No common ancestor!';
    }
    return result;
}
