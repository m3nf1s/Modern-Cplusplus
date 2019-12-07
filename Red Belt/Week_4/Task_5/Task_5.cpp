/*
    Рассмотрим упрощённый текстовый редактор, поддерживающий следующий набор команд:

    *   Перемещение курсора влево (Left) и вправо (Right) на одну позицию.
    *   Ввод символа в текущую позицию курсора (Insert).
    *   Копирование фрагмента текста, начинающегося в текущей позиции курсора, в буфер обмена (Copy).
    *   Вырезание фрагмента текста аналогично копированию с последующим удалением скопированных символов из текста (Cut).
    *   Вставка содержимого буфера обмена в текущую позицию курсора (Paste).
    Эти команды действительно поддерживаются практически любым текстовым редактором.

    Также для команд действуют стандартные правила, определяющие их эффект:
    *   Если редактор содержит текст длиной n символов, то курсор может находиться в одной из (n + 1) возможных позиций.
        Например, обозначим курсор вертикальной чертой | (это обозначение мы будем использовать в дальнейшем),
            тогда в тексте abc курсор может располагаться в 4 позициях: |abc, a|bc, ab|c, abc|.
        Поэтому команда Left не имеет эффекта, когда курсор расположен в начале текста, а Right не имеет эффекта,
            когда курсор находится в конце. В частности, ни Left, ни Right не имеют эффекта, когда редактор не содержит текста.
   
    *   Введённый символ располагается в позиции курсора, сдвигая курсор и весь текст справа от него на одну позицию вправо.
        Аналогично, при вставке фрагмента длиной n курсор и текст справа от него смещаются на n позиций вправо.
        В таблице ниже приведены примеры, демонстрирующие данное правило.
    
    *   Буфер обмена изначально пуст. Вставка пустого фрагмента не имеет эффекта.
        Содержимое буфера не сбрасывается после вставки, а остается неизменным до следующей команды Copy или Cut.
        Копирование или вырезание фрагмента нулевой длины не оказывает влияния на текст, но опустошает буфер обмена.
        Курсор не смещается ни при копировании, ни при вырезании текста.
        Например, после вырезания из текста ab|cdef фрагмента из трёх символов, получим текст ab|f.
    
    Вам предстоит реализовать «ядро» текстового редактора, поддерживающего все описанные операции, в виде класса Editor.
    Как можно заметить, каждой описанной команде сопоставлен метод класса Editor.
    Также введён метод GetText(), позволяющий получить текущее содержимое редактора в виде строки.
    В комментариях к методам Cut(size_t tokens) и Copy(size_t tokens) указано,
        что в буфер обмена попадает фрагмент длиной не более tokens символов — это означает, что,
        если справа от курсора располагается менее, чем tokens символов,
        методы Cut() и Copy() должны вырезать/скопировать все символы справа.
    
    Ограничения
    Реализация класса Editor должна обрабатывать 10^6 запросов не более чем за 1 секунду.
    При этом гарантируется, что:
    *   длина текста никогда не превышает 10^6 символов;
    *   методы Copy() и Cut() суммарно копируют/вырезают не более 10^6 символов;
    *   метод GetText() вызывается один раз в каждом из тестов.
*/
#include "profiler.h"
#include <string>
#include "test_runner.h"
#include <list>
class Editor
{
public:
    Editor()
        : cursor_(text_.end())
    {
    }

    void Left()
    {
        if (cursor_ != text_.begin())
        {
            --cursor_;
        }
    }
    void Right()
    {
        if (cursor_ != text_.end())
        {
            ++cursor_;
        }
    }
    void Insert(char token)
    {
        text_.insert(cursor_, token);
    }
    void Cut(size_t tokens = 1)
    {
        auto it = cursor_;
        MoveCursor(tokens);
        buffer_.assign(it, cursor_);
        text_.erase(it, cursor_);
    }
    void Copy(size_t tokens = 1)
    {
        auto it = cursor_;
        MoveCursor(tokens);
        buffer_.assign(it, cursor_);
    }
    void Paste()
    {
        text_.insert(cursor_, buffer_.begin(), buffer_.end());
    }
    std::string GetText() const
    {
        return { text_.begin(), text_.end() };
    }
private:
    std::list<char> text_;
    std::list<char> buffer_;
    std::list<char>::iterator cursor_;
    
    void MoveCursor(size_t tokens)
    {
        for (size_t i = 0; i < tokens; i++)
        {
            Right();
        }
    }
};

void TypeText(Editor& editor, const std::string& text)
{
    for (char c : text)
    {
        editor.Insert(c);
    }
}

void TestEditing() 
{
    LOG_DURATION("TestEditing");
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i)
        {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for (size_t i = 0; i < text_len - first_part_len; ++i)
        {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse()
{
    LOG_DURATION("TestReverse");
    Editor editor;

    const std::string text = "esreveR";
    for (char c : text) 
    {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText()
{
    LOG_DURATION("TestNoText")
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer()
{
    LOG_DURATION("TestEmptyBuffer");
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main()
{
    LOG_DURATION("Total");
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}