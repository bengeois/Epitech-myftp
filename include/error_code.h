/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#ifndef NWP_MYFTP_2019_ERROR_CODE_H
#define NWP_MYFTP_2019_ERROR_CODE_H

#define E_120 "120 Service ready in %i minutes.\r\n"
#define E_125 "125 Data connection already open; transfer starting.\r\n"
#define E_150 "150 File status okay; about to open connection.\r\n"
#define E_200 "200 Command okay.\r\n"
#define E_214 "214 Help OK.\r\n"
#define E_214CD "214 %s : %s.\r\n"
#define E_214C "214 The following commands are recognized\r\n"
#define E_220 "220 Service ready for new user.\r\n"
#define E_221 "221 Service closing control connection.\r\n"
#define E_226 "226 Closing data connection.\r\n"
#define E_227 "227 Entering Passive Mode (%s,%s,%s,%s,%s,%s).\r\n"
#define E_230 "230 User logged in, proceed.\r\n"
#define E_230A "230 Already logged in.\r\n"
#define E_250 "250 Requested file action okay, completed.\r\n"
#define E_257 "257 "%s" created.\r\n"
#define E_331 "331 User name okay, need password.\r\n"
#define E_332 "332 Need account for login.\r\n"
#define E_500 "500 Unknown command.\r\n"
#define E_503 "503 Login with USER first.\r\n"
#define E_530P "530 Permission denied.\r\n"
#define E_530C "530 Can't change from guest user.\r\n"
#define E_530L "530 Login incorrect.\r\n"
#define E_530PL "530 Please login with USER and PASS.\r\n"

#endif //NWP_MYFTP_2019_ERROR_CODE_H
