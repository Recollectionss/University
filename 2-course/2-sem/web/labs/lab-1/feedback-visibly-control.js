const feedback_content = document.getElementById('feedback-content');

const  feedback_show_1 = document.getElementById('feedback-show-1');
const  feedback_show_2 = document.getElementById('feedback-show-2');

const feedback_send_button = document.getElementById('btn-feedback');

feedback_show_1.addEventListener('click',()=>{
    feedback_content.classList.remove('hide');
});
feedback_show_2.addEventListener('click',()=>{
    feedback_content.classList.remove('hide');
});
feedback_send_button.addEventListener('click',()=>{
    feedback_content.classList.add('hide');
});