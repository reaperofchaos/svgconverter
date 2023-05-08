# XML PARSER
Tool to parse XML

# Grammar
## NON-TERMINAL SYMBOLS
N = {<, >, !, {, }, \s,\t, \n, \r, “, ’, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R,
S, T, U, V, W, X, Y, Z, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w,x,y,
z, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, [, ], (, ), @, #, $, %, ^, &, *, _, -, +, =, ~, `, ?, ,, ., :, ;, \, /, |, }

## TERMINAL SYMBOLS 
T = {}

 ## START SYMBOL
 S = {STMT}

 ## Production Rules
 ```
 P={
    // A document tag with one or more tags
    //Or just a tag
	STMT = DocumentTag + Element | ELement,
    
    //Characters (Tokens)
    Character = Character | WhiteSpace | Number | Letter | Symbol | UnicodeCharacter | Unknown | Character + Character

    //Symbols
    Symbol = NotASymbol | Symbol | Quote | SingleQuote | EscapedQuote | EscapedSingleQuote| Colon | Comma | OpenBracket | CloseBracket | ObjectOpenBracket | ObjectCloseBracket |ArrayOpenBracket | ArrayCloseBracket | Exclamation | Dash | Underscore | QuestionMark |ForwardSlash | ClosingCloseTag | EqualSymbol | Semicolon | Percentage | HashTag

    WhiteSpaces = \s | \t | \n | \r
    Symbol = @ | $ | ^ | & | * | ( | ) | + | ` | ~ | . | | | \
    Percentage = %
    Comma = ,
    Semicolon = ;
    Underscore = _
    EqualSymbol = =
    HashTag = #
    SingleQuote = '
    Quote = "
    EscapedSingleQuote = \'
    EscapedQuote = \"
    ObjectOpenBracket = {
    ObjectCloseBracket = }
    ArrayOpenBracket = [
    ArrayCloseBracket = ]
    Colon = : 
    QuestionMark = ?
    CloseBracket = >
    OpenBracket = <
    Dash = - 
    ForwardSlash = /

    //Letters
    Letter = Uppercase | Lowercase

    Lowercase = a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p
    | q | r | s | t | u | v | w | x | y | z 

    Uppercase = A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P
    | Q | R | S | T | U | V | W | X | Y | Z

    //Numbers
    Number = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 

    //Components
    Component = Name | StringType | ArrayType | ObjectType | NumberType | Unknown | CloseObject | OpenObject | OpenTag | CloseTag | OpenArray | CloseArray | ColonComponent | CommaComponent | ExclamationComponent | QuestionComponent | DashComponent | SemicolonComponent | WhiteSpaces | ClosingCloseTag | ClosingOpenTag | EqualComponent | DocumentTypeOpenTag | CommentOpenTag | CommentCloseTag | PercentageComponent | HashTagComponent

    NumberType = number | number + number
    CloseTag = CloseBracket
    CloseArray = ArrayCloseBracket
    CloseObject = ObjectCloseBracket
    WhiteSpaces = WhiteSpace | WhiteSpace + WhiteSpace
    Name = Letter | Letter + Letter
    ClosingCloseTag = ForwardSlash + CloseBracket
    StringType = Character | Character + Character
    OpenArray = ArrayOpenBracket
    OpenObject = ObjectOpenBracket
    ExclamationComponent = Exclamation
    EqualComponent = EqualSymbol
    SemicolonComponent = Semicolon
    ColonComponent = Colon
    PercentageComponent = Percentage
    CommaComponent = Comma
    HashTagComponent = HashTag
    ClosingOpenTag = OpenBracket + ForwardSlash
    CommentOpenTag = OpenBracket + Exclamation + Dash + Dash
    CommentCloseTag = Dash + Dash + CloseBracket
    DocumentTypeOpenTag = OpenBracket + Exclamation
    OpenTag = OpenBracket

    //Primitives
    Primitive = Primitive | StringPrimitive | NumberPrimitive | BooleanPrimitive | ArrayPrimitive | ObjectPrimitive

    BooleanPrimitive = Name
    StringPrimitive = StringType | StringType + StringType
    NumberPrimitive = NumberType | NumberType + NumberType
    ObjectPairs = Name + ColonComponent + Primitive
    ObjectPrimitive = ObjectPairs | ObjectPairs + ObjectPairs
    ArrayPrimitive = Primitive | Primitive + CommaComponent +  Primitive

    //Props 
    Prop = Prop | ObjectProp | StringProp | BooleanProp
    StringProp = Name + EqualComponent + StringPrimitive
    ObjectProp = Name + EqualComponent + ObjectPrimitive
    BooleanProp = Name | Name + EqualComponent + BooleanPrimitive

    //Elements
    Element = Element | DocumentTag | Tag | NestedObject | NestedString
    DocumentTag = DocumentTypeOpenTag + Name + Prop + CloseTag
    OpenTagElement = OpenTag + Name + Prop + CloseTag
    SelfClosingTagElement = OpenTag + Name + Prop + ClosingCloseTag
    CloseTagElement = ClosingOpenTag + Name + CloseTag
    CommentTagElement = CommentOpenTag + Component + CommentCloseTag
    NestedString = Component 
    
    //Tag
    Tag = Tag | OpenTagElement | SelfClosingTagElement | CloseTagElement | CommentTagElement | NotATag

```

## Logic
Character (Token) -> Component (one or more tokens) -> Primitive, Element