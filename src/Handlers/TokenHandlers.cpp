#include "TokenHandlers.h"
/**
 * @brief Builds a Number component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param numbers
 * @return std::shared_ptr<NumberType>
 */
std::shared_ptr<NumberType> TokenHandlers::buildNumberComponent(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    std::vector<std::shared_ptr<Number>> &numbers)
{

    while (m_tokens[m_index]->type() == CharacterType::Number)
    {
        numbers.push_back(std::make_shared<Number>(m_tokens[m_index]->getValue()));
        CharacterUtilities::IncrementIndex(m_tokens, m_index);
    }
    return std::make_shared<NumberType>(numbers);
}

/**
 * @brief builds a close tag made up
 * of white space and a >
 *
 * @param m_tokens list of characters
 * @param m_index the current index in the list
 * @return std::shared_ptr<CloseTag>
 */
std::shared_ptr<CloseTag> TokenHandlers::buildCloseTag(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<CloseTag>(
        std::dynamic_pointer_cast<GreaterThanSymbol>(m_tokens[start]));
}

/**
 * @brief Builds a close array component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<CloseArray>
 */
std::shared_ptr<CloseArray> TokenHandlers::buildCloseArray(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<CloseArray>(std::dynamic_pointer_cast<RightSquareBracket>(m_tokens[start]));
}

/**
 * @brief Builds a close object component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<CloseObject>
 */
std::shared_ptr<CloseObject> TokenHandlers::buildCloseObject(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    CharacterUtilities::IgnoreWhiteSpace(m_tokens, m_index);

    return std::make_shared<CloseObject>(std::dynamic_pointer_cast<RightCurlyBracket>(m_tokens[start]));
}

/**
 * @brief Builds whitespaces component from the provided characters
 *
 * @param whiteSpaces
 * @return std::shared_ptr<WhiteSpaces>
 */
std::shared_ptr<WhiteSpaces> TokenHandlers::buildWhiteSpaces(
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{
    return std::make_shared<WhiteSpaces>(whiteSpaces);
}

/**
 * @brief Builds a name component. It is a set of characters with no
 * whitespaces and has to start with a letter
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @param characters
 * @return std::shared_ptr<Name>
 */
std::shared_ptr<Name> TokenHandlers::buildName(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start,
    std::vector<std::shared_ptr<Character>> &characters)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    do
    {
        characters.push_back(std::dynamic_pointer_cast<Character>(m_tokens[m_index]));
        CharacterUtilities::IncrementIndex(m_tokens, m_index);
    } while (m_tokens[m_index]->type() != CharacterType::WhiteSpace &&
             (m_tokens[m_index]->symbolType() != SymbolType::ForwardSlash) &&
             (m_tokens[m_index]->symbolType() != SymbolType::GreaterThanSymbol) &&
             (m_tokens[m_index]->symbolType() != SymbolType::LessThanSymbol) &&
             (m_tokens[m_index]->symbolType() != SymbolType::RightParenthesis) &&
             (m_tokens[m_index]->symbolType() != SymbolType::EqualSymbol) &&
             (m_tokens[m_index]->symbolType() != SymbolType::Colon) &&
             ((m_tokens[m_index]->symbolType() != SymbolType::Dash) &&
              (m_tokens[m_index + 1]->symbolType() != SymbolType::Dash)) &&
             (m_tokens[m_index]->symbolType() != SymbolType::Comma) &&
             (m_tokens[m_index]->symbolType() != SymbolType::Semicolon));
    std::cout << "next char after name" << m_tokens[m_index]->inspect() << "\n";
    if (m_tokens[start]->getType() == "Period Symbol")
    {
        return std::make_shared<Name>(
            std::dynamic_pointer_cast<PeriodSymbol>(m_tokens[start]),
            characters);
    }

    return std::make_shared<Name>(
        std::dynamic_pointer_cast<Letter>(m_tokens[start]),
        characters);
}

/**
 * @brief Builds a closing close tag component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<ClosingCloseTag>
 */
std::shared_ptr<ClosingCloseTag> TokenHandlers::buildClosingCloseTag(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    CharacterUtilities::IgnoreWhiteSpace(m_tokens, m_index);
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<ClosingCloseTag>(
        std::dynamic_pointer_cast<ForwardSlash>(m_tokens[start]),
        std::dynamic_pointer_cast<GreaterThanSymbol>(m_tokens[m_index - 1]));
}

/**
 * @brief Builds a string component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param characters
 * @param symbolType
 * @return std::shared_ptr<StringType>
 */
std::shared_ptr<StringType> TokenHandlers::buildString(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    std::vector<std::shared_ptr<Character>> &characters,
    SymbolType symbolType)
{

    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    if (symbolType == SymbolType::SingleQuote)
    {
        while (m_tokens[m_index]->symbolType() != SymbolType::SingleQuote)
        {
            characters.push_back(m_tokens[m_index]);
            CharacterUtilities::IncrementIndex(m_tokens, m_index);
        }

        CharacterUtilities::IncrementIndex(m_tokens, m_index);

        return std::make_shared<StringType>(characters);
    }
    else
    {
        while (m_tokens[m_index]->symbolType() != SymbolType::Quote)
        {
            characters.push_back(m_tokens[m_index]);
            CharacterUtilities::IncrementIndex(m_tokens, m_index);
        }

        CharacterUtilities::IncrementIndex(m_tokens, m_index);

        return std::make_shared<StringType>(characters);
    }
}

/**
 * @brief Builds an open array component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<OpenArray>
 */
std::shared_ptr<OpenArray> TokenHandlers::buildOpenArray(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<OpenArray>(
        std::dynamic_pointer_cast<LeftSquareBracket>(m_tokens[start]));
}

/**
 * @brief Creates an open object component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<OpenObject>
 */
std::shared_ptr<OpenObject> TokenHandlers::buildOpenObject(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    return std::make_shared<OpenObject>(
        std::dynamic_pointer_cast<LeftCurlyBracket>(m_tokens[start]));
}

/**
 * @brief Builds an exclamation component from the provided character
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<ExclamationComponent>
 */
std::shared_ptr<ExclamationComponent> TokenHandlers::buildExclamation(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{

    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<ExclamationComponent>(
        std::dynamic_pointer_cast<Exclamation>(m_tokens[start]));
}

/**
 * @brief Builds an and component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<AndComponent>
 */
std::shared_ptr<AndComponent> TokenHandlers::buildAndComponent(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{

    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<AndComponent>(
        std::dynamic_pointer_cast<AndSymbol>(m_tokens[start]));
}

/**
 * @brief Builds an equal component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<EqualComponent>
 */
std::shared_ptr<EqualComponent> TokenHandlers::buildEqual(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<EqualComponent>(
        std::dynamic_pointer_cast<EqualSymbol>(m_tokens[start]));
}

/**
 * @brief Builds a semicolon from the provided semicolon characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<SemicolonComponent>
 */
std::shared_ptr<SemicolonComponent> TokenHandlers::buildSemicolon(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    CharacterUtilities::IgnoreWhiteSpace(m_tokens, m_index);

    return std::make_shared<SemicolonComponent>(
        std::dynamic_pointer_cast<Semicolon>(m_tokens[start]));
}

/**
 * @brief Builds a colon component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<ColonComponent>
 */
std::shared_ptr<ColonComponent> TokenHandlers::buildColon(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<ColonComponent>(
        std::dynamic_pointer_cast<Colon>(m_tokens[start]));
}

/**
 * @brief Builds a percentage component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<PercentageComponent>
 */
std::shared_ptr<PercentageComponent> TokenHandlers::buildPercentage(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<PercentageComponent>(
        std::dynamic_pointer_cast<Percentage>(m_tokens[start]));
}

/**
 * @brief Builds a comma component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<CommaComponent>
 */
std::shared_ptr<CommaComponent> TokenHandlers::buildComma(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<CommaComponent>(
        std::dynamic_pointer_cast<Comma>(m_tokens[start]));
}

/**
 * @brief Builds a hashtag component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<HashTagComponent>
 */
std::shared_ptr<HashTagComponent> TokenHandlers::buildHashTag(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<HashTagComponent>(
        std::dynamic_pointer_cast<HashTag>(m_tokens[start]));
}

/**
 * @brief Builds a nested string from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param characters
 * @return std::shared_ptr<StringType>
 */
std::shared_ptr<StringType> TokenHandlers::buildNestedString(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    std::vector<std::shared_ptr<Character>> &characters)
{
    characters.push_back(m_tokens[m_index]);
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    while (
        m_tokens[m_index]->symbolType() != SymbolType::LessThanSymbol &&
        m_tokens[m_index]->symbolType() != SymbolType::LeftCurlyBracket &&
        m_tokens[m_index]->symbolType() != SymbolType::Dash)
    {
        characters.push_back(m_tokens[m_index]);
        CharacterUtilities::IncrementIndex(m_tokens, m_index);
    }

    return std::make_shared<StringType>(characters);
}

/**
 * @brief Builds a closing open tag from the provided character
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<ClosingOpenTag>
 */
std::shared_ptr<ClosingOpenTag> TokenHandlers::buildClosingOpenTag(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    CharacterUtilities::IgnoreWhiteSpace(m_tokens, m_index);

    return std::make_shared<ClosingOpenTag>(
        std::dynamic_pointer_cast<LessThanSymbol>(m_tokens[start]),
        std::dynamic_pointer_cast<ForwardSlash>(m_tokens[m_index - 1]));
}

/**
 * @brief Builds a comment open tag from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<CommentOpenTag>
 */
std::shared_ptr<CommentOpenTag> TokenHandlers::buildCommentOpenTag(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    CharacterUtilities::IgnoreWhiteSpace(m_tokens, m_index);
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    CharacterUtilities::IgnoreWhiteSpace(m_tokens, m_index);
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    CharacterUtilities::IgnoreWhiteSpace(m_tokens, m_index);

    return std::make_shared<CommentOpenTag>(
        std::dynamic_pointer_cast<LessThanSymbol>(m_tokens[start]),
        std::dynamic_pointer_cast<Exclamation>(m_tokens[start + 1]),
        std::dynamic_pointer_cast<Dash>(m_tokens[start + 2]),
        std::dynamic_pointer_cast<Dash>(m_tokens[start + 3]));
}

/**
 * @brief Builds a comment close component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<CommentCloseTag>
 */
std::shared_ptr<CommentCloseTag> TokenHandlers::buildCommentCloseTag(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{

    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    return std::make_shared<CommentCloseTag>(
        std::dynamic_pointer_cast<Dash>(m_tokens[start]),
        std::dynamic_pointer_cast<Dash>(m_tokens[start + 1]),
        std::dynamic_pointer_cast<GreaterThanSymbol>(m_tokens[m_index - 1]));
}

/**
 * @brief Builds a document open tag from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<DocumentTypeOpenTag>
 */
std::shared_ptr<DocumentTypeOpenTag> TokenHandlers::buildDocumentTypeOpenTag(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{

    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    CharacterUtilities::IgnoreWhiteSpace(m_tokens, m_index);

    return std::make_shared<DocumentTypeOpenTag>(
        std::dynamic_pointer_cast<LessThanSymbol>(m_tokens[start]),
        std::dynamic_pointer_cast<Exclamation>(m_tokens[m_index - 1]));
}

/**
 * @brief Function to find white space and add it to the whitespaces vector
 *
 * @param m_tokens
 * @param m_index
 * @param whiteSpaces
 */
void TokenHandlers::findWhiteSpace(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{
    if (m_tokens[m_index + 1]->type() == CharacterType::WhiteSpace)
    {
        CharacterUtilities::IncrementIndex(m_tokens, m_index);
        while (m_tokens[m_index]->type() == CharacterType::WhiteSpace)
        {
            whiteSpaces.push_back(std::make_shared<WhiteSpace>(m_tokens[m_index]->getValue()));
            CharacterUtilities::IncrementIndex(m_tokens, m_index);
        }
    }
}

/**
 * @brief Builds an open tag from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<OpenTag>
 */
std::shared_ptr<OpenTag> TokenHandlers::buildOpenTag(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IgnoreWhiteSpace(m_tokens, m_index);

    return std::make_shared<OpenTag>(
        std::dynamic_pointer_cast<LessThanSymbol>(m_tokens[start]));
}

/**
 * @brief Builds a close parenthesis component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<CloseParenthesisComponent>
 */
std::shared_ptr<CloseParenthesisComponent> TokenHandlers::buildCloseParenthesis(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<CloseParenthesisComponent>(
        std::dynamic_pointer_cast<RightParenthesis>(m_tokens[start]));
}

/**
 * @brief Builds an open parenthesis component from the provided characters
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<OpenParenthesisComponent>
 */
std::shared_ptr<OpenParenthesisComponent> TokenHandlers::buildOpenParenthesis(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<OpenParenthesisComponent>(
        std::dynamic_pointer_cast<LeftParenthesis>(m_tokens[start]));
}

/**
 * @brief Builds an open root component from the provided characters ex "<?"
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<OpenRootComponent>
 */
std::shared_ptr<OpenPrologComponent> TokenHandlers::buildOpenPrologComponent(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    return std::make_shared<OpenPrologComponent>(
        std::dynamic_pointer_cast<LessThanSymbol>(m_tokens[start]),
        std::dynamic_pointer_cast<QuestionMark>(m_tokens[m_index - 1]));
}

/**
 * @brief Builds a close root component from the provided characters ex "<?"
 *
 * @param m_tokens
 * @param m_index
 * @param start
 * @return std::shared_ptr<CloseRootComponent>
 */
std::shared_ptr<ClosePrologComponent> TokenHandlers::buildClosePrologComponent(
    std::vector<std::shared_ptr<Character>> &m_tokens,
    size_t &m_index,
    size_t &start)
{
    CharacterUtilities::IncrementIndex(m_tokens, m_index);
    CharacterUtilities::IgnoreWhiteSpace(m_tokens, m_index);
    CharacterUtilities::IncrementIndex(m_tokens, m_index);

    return std::make_shared<ClosePrologComponent>(
        std::dynamic_pointer_cast<QuestionMark>(m_tokens[start]),
        std::dynamic_pointer_cast<GreaterThanSymbol>(m_tokens[m_index - 1]));
}