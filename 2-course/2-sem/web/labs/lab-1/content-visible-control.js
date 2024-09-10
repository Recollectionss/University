const nav_main = document.getElementById('nav_main');
const nav_catalog = document.getElementById('nav_catalog');
const nav_contacts = document.getElementById('nav_contacts');

const contents = {
    content_main: document.getElementById('main-content'),
    content_catalog: document.getElementById('catalog-section'),
    content_contacts: document.getElementById('contacts'),
    hide_all_beside: function (not_hide) {
        Object.values(this).forEach(el => {
            if (el !== not_hide && el instanceof HTMLElement) {
                el.classList.add('hide');
            } else if (el === not_hide && el instanceof HTMLElement) {
                el.classList.remove('hide');
            }
        });
    }
};

nav_main.addEventListener('click',()=>{
    contents.hide_all_beside(contents.content_main);
});
nav_catalog.addEventListener('click',()=>{
    contents.hide_all_beside(contents.content_catalog);
});
nav_contacts.addEventListener('click',()=>{
    contents.hide_all_beside(contents.content_contacts);
});