const h1Element = document.querySelector('.contacts-main-text h1');

const ulContacts = document.querySelector('.ul-contacts ul');

h1Element.addEventListener('mouseenter', function() {
    ulContacts.querySelectorAll('li').forEach(li => {
        li.style.fontSize = '1.2em';
        li.style.color = 'orangered';
    });
});

h1Element.addEventListener('mouseleave', function() {
    ulContacts.querySelectorAll('li').forEach(li => {
        li.style.fontSize = '';
        li.style.color = '';
    });
});
