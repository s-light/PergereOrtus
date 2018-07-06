'use strict';

window.addEventListener('load', function(event) {
    showBrowserInfo();
});

function showBrowserInfo() {
    console.group('show browser info');
    let result = '';
    let el_info = document.querySelector('#browser_info');
    if (el_info) {
        result = getBrowserInfo();
        el_info.textContent = result;
    }
    console.groupEnd();
}

function getBrowserInfo() {
    // https://stackoverflow.com/questions/1248081/get-the-browser-viewport-dimensions-with-javascript?rq=1
    let result = '';
    result += 'Viewport:\n';
    result += 'document.documentElement.clientWidth';
    result += '   ';
    result += document.documentElement.clientWidth;
    result += ' - ';
    result += document.documentElement.clientHeight;
    result += '\n';
    result += 'window.innerWidth                   ';
    result += '   ';
    result += window.innerWidth;
    result += ' - ';
    result += window.innerHeight;
    result += '\n';
    result += 'window.outerWidth                   ';
    result += '   ';
    result += window.outerWidth;
    result += ' - ';
    result += window.outerHeight;
    result += '\n';

    result += '\n';

    result += 'Device:\n';
    result += 'window.screen.width                 ';
    result += '   ';
    result += window.screen.width;
    result += ' - ';
    result += window.screen.height;
    result += '\n';
    result += 'window.screen.availWidth            ';
    result += '   ';
    result += window.screen.availWidth;
    result += ' - ';
    result += window.screen.availHeight;
    result += '\n';

    result += '\n';

    result += 'Document:\n';
    result += 'document.body.clientWidth           ';
    result += '   ';
    result += document.body.clientWidth;
    result += ' - ';
    result += document.body.clientHeight;
    result += '\n';
    result += 'document.body.offsetWidth           ';
    result += '   ';
    result += document.body.offsetWidth;
    result += ' - ';
    result += document.body.offsetHeight;
    result += '\n';
    result += 'document.body.scrollWidth           ';
    result += '   ';
    result += document.body.scrollWidth;
    result += ' - ';
    result += document.body.scrollHeight;
    result += '\n';
    result += 'document.documentElement.clientWidth';
    result += '   ';
    result += document.documentElement.clientWidth;
    result += ' - ';
    result += document.documentElement.clientHeight;
    result += '\n';
    result += 'document.documentElement.offsetWidth';
    result += '   ';
    result += document.documentElement.offsetWidth;
    result += ' - ';
    result += document.documentElement.offsetHeight;
    result += '\n';
    result += 'document.documentElement.scrollWidth';
    result += '   ';
    result += document.documentElement.scrollWidth;
    result += ' - ';
    result += document.documentElement.scrollHeight;
    result += '\n';

    return result;
}
