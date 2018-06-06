

function findNearest(start_element, selector) {
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
            let smallest = level_distances.slice().sort()[0];
            // now check if there are duplicates of level_distance
            let duplicate_levels = [];
            let smallest_levels = {
                value: 9999999,
                index: -1,
            };
            for (let entry of level_distances.entries()) {
                let index = entry[0];
                let value = entry[1];
                console.log('index', index, 'value', value);
                console.log('smallest_levels', smallest_levels);
                console.log(
                    'value < smallest_levels.value',
                    value < smallest_levels.value);
                if (value < smallest_levels.value) {
                    smallest_levels.index = index;
                    smallest_levels.value = value;
                    if (duplicate_levels.length == 0) {
                        duplicate_levels.push(index);
                    }
                } else {
                    console.log(
                        'value === smallest_levels.value',
                        value === smallest_levels.value);
                    if (value === smallest_levels.value) {
                        duplicate_levels.push(index);
                    }
                }
            }
            console.log('duplicate_levels', duplicate_levels);
            if (duplicate_levels.length == 1) {
                result_element = element_list[smallest_levels.index];
            }


            // let result_list = findNearestRecursive(start_element, selector);
            // let nearest = {};
            // for (let current of result_list) {
            //     if (current.distance < nearest.distance) {
            //         nearest = current;
            //     }
            // }
            // result_element = nearest.element;
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
        if (distanceElement1ToCommon !== distanceElement2ToCommon) {
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


function findNearestRecursive(start_element, selector) {
    let result = [];

    let result_obj = {
        element: null,
        distance: 0,
    };
    // check if selector is a child
    // let child_element_list = start_element.querySelectorAll(selector);
    //
    // if (child_element_list.length > 0) {
    //
    // }

    // check if parent element contains selector
    let parent_element_list =
        start_element.parentElement.querySelectorAll(selector);

    let subresult = findNearestRecursive();
    result.concat(subresult);

    return result;
}

function checkChilds(start_element, selector) {
    let result_obj = {
        element: null,
        distance: 0,
    };
    return result_obj;
}








class FormulaTable {
    constructor(table_element, column_meaning, update_order) {
        this.table_element = table_element;
        this.column_meaning = column_meaning;
        this.update_order = update_order;
    }

    getValue(element_id) {
        let value = undefined;
        // let el = document.querySelector('#' + element_id);
        // if (el) {
        //     // check if element is input
        //     if (el.nodeName == 'INPUT') {
        //         // get value
        //         value = parseFloat(el.value);
        //     } else {
        //         // get content
        //         value = parseFloat(el.textContent);
        //     }
        // }
        return value;
    }

    setValue(element_id, value) {
        // let el = document.querySelector('#' + element_id);
        // if (el) {
        //     // check if element is input
        //     if (el.nodeName == 'INPUT') {
        //         // set value
        //         el.value = value;
        //     } else {
        //         // set content
        //         el.textContent = value;
        //     }
        // }
    }

    update_table(event) {
        console.log('update_table:', event);
    }

    update_table_below(event) {
        console.log('update_table_below:', event);
    }

};
