* |================================================================================|
* |                                                                                | 
* |                             SITIOS UTILES PARA 68K                             |  
* |                         ~ Mucho Animo con el Proyecto ~                        |       
* |       ~ AVISO: Si copiais esto os saltará copia y encima no funcionara ~	     |                  
* |                                                                                |
* |================================================================================|

        * http://68k.hax.com/
        * http://mrjester.hapisan.com/04_MC68/
        * https://ascii.cl/
        * https://www.rapidtables.com/convert/number/ascii-to-hex.html

* Se Anotan algunas paginas del PDF del Manual, para ayudar a guiaros un poco.

        ORG     $0
        DC.L    $8000           * Posicion de la Pila
        DC.L    INICIO          * Posicion del PC
*		  DC.L	PRUEBA

* |================================================================================|
* |                                                                                | 
* |                      	   Enunciado del Problema                            |
* |                                                                                | 
* |     Se busca hacer una cuestion similar al printf que se puede ver en otros    |
* |     lenguajes, de tal forma que "p patata x" imprima "patata". 	           |
* |     Para simplificar, la linea A siempre sera de recepcion y la     	     |
* |     B siempre sera de transmision.							     |	
* |                                                                                | 
* |================================================================================|

* NOTA: Se podria hacer un printf de verdad y en condiciones, pero por desgracia el BSVC 
* (Al menos mi version de Windows) no acepta caracteres especiales por lo que se complicaria 
* bastante hacerlo xDDD

* |================================================================================|
* |                                                                                | 
* |                      Tabla de Registros de Duart                               |
* |                              Manual P. 43                                      |
* |                                                                                |
* |================================================================================|

        ORG     $400

*Linea A

MR1A            EQU     $effc01       	* De modo A (Linea A)
MR2A            EQU     $effc01       	* De modo A (Linea A)
SRA             EQU     $effc03       	* De estado A (lectura)
CSRA            EQU     $effc03       	* De seleccion de reloj A (escritura)
CRA             EQU     $effc05       	* De control A (escritura) y Sin Acceso
RBA             EQU     $effc07       	* Buffer recepcion A  (lectura)
TBA             EQU     $effc07       	* Buffer de transmision A (escritura)
ACR             EQU	$effc09	      * De control auxiliar
ISR             EQU     $effc0B       	* De estado de interrupcion A (lectura)
IMR             EQU     $effc0B       	* De mascara de interrupcion A (escritura)

* Linea B

MR1B	        EQU     	$effc11		* De modo B (Linea B)
MR2B	        EQU     	$effc11		* De modo B (Linea B)
SRB 	        EQU		$effc13		* De estado B (lectura)
CSRB	        EQU		$effc13		* De seleccion de reloj B (escritura)
CRB           EQU    	$effc15		* De control B (escritura)
TBB 	        EQU 	$effc17		* Buffer de transmision B (escritura)
RBB           EQU     	$effc17		* Buffer de recepcion B (lesctura)

* Ambas Lineas

IVR	        EQU		$effc19		* De vector de interrupcion (escritura y lectura)
*             EQU     	$effc1b         * Sin Implementar x2
*             EQU     	$effc1d         * Sin Implementar x2
*             EQU     	$effc1F         * Sin Implementar x2

* Registro de Estado de Interrupcion, pagina 47 manual (Aqui solo nos interesan RA y TB pero hay RB y TA tambien)
RXRDYA	  EQU	1
TXRDYB	  EQU	4

IMRC          DS.B    1       * Aqui guardamos la copia del IMR
                                * Necesaria porque IMR no se puede 
                                * leer. Pg. 67 manual 1.1

* |================================================================================|
* |                                                                                | 
* |                             Datos y Variables                                  |
* |                                                                                |
* |================================================================================|

* Cada puerto viene denominado por su codigo en binario que os indican en el enunciado (pg 65 pdf)
* Aqui nos sobran varios porque hemos simplificado a solo RA y TB, por lo que esto tambien simplifica.
* Por lo tanto, el bit 0 es el Unico que nos importa
* 8 Bits:   00000000
* Posicion: 76543210
* Por lo tanto, bastaria con enmascarar con AND.L, MASK o usando btst, y comprobar que el bit 0 es 0 o 1 
* Recepcion Linea A:   00000000 = 0x0
* Transmision Linea B: 00000001 = 0x1

PORT_RA	        EQU	0
PORT_TB	        EQU	1

* Zona de Buffers
BUF_RA          	  DS.B    500   * Buffer de Recepcion A
BUF_TB          	  DS.B    500   * Buffer de Transmision B
FINBUFTB            DS.B    1     * Fin de la Zona de Buffers (No usar esto es un poco coñazo)

* Zona de Punteros
PTR_RI		DC.L	1	* Puntero de Insercion
PTR_RX		DC.L	1	* Puntero de Extraccion 

PTR_TI		DC.L	1	* Puntero de Insercion
PTR_TX		DC.L	1	* Puntero de Extraccion 

FLG_PRNT		DC.L  1     * FLAG que nos dice si hemos detectado un print

* Mas info de la RTI en pg. 71 del Manual

RTI:            MOVEM.L D0-D2,-(A7) 	        * Guarda los registros que se usan en la pila
                EOR.L D2,D2
                * Seccion de Identificacion de Interrupcion
RTI_BUC:        MOVE.B ISR,D2                   * Cargamos el ISR en D1
                                                * (Interruption State Register)
                                                * Basicamente nos dice donde hubo una interrupción
                AND.B IMRC,D2                   * El ISR se enmascara con el IMR, pg. 40 del manual 1.1
                                                * Esencialmente es un filtro que nos permite decidir qué
                                                * Interrupciones consideramos importantes
                                                
                * Las operaciones se deben negar aqui, porque BTST funciona de tal forma que el valor TRUE 
                * es que un bit determinado sea igual a 0
                BTST #TXRDYB,D2                 * Si el origen no es transmisión por linea A
                        BNE RTI_TB              * !(D1 & 0b00010000) == Vamos a transmision de A
                BTST #RXRDYA,D2                 * Si el origen no es transmisión por linea A
                        BNE RTI_RA              * !(D1 & 0b00100000) == Vamos a transmision de A
                BRA RTIEND
		    EOR.L D0,D0
                * Zona de Recepcion
RTI_RA:         MOVE.L #PORT_RA,D0              * Cargamos el puerto RA para ESCCAR
		    EOR.L D1,D1
		    MOVE.B RBA,D1                   * Cargamos el caracter del puerto de recepcion a

* COMPROBACION DE IMPRESION

* Solo pasamos chars dentro de print
		    CMP.B   #0,FLG_PRNT			* Si es 0 -> COMPROBAMOS SI CHAR ES 'P'
			BNE PRNT_MOD			* Si es 0, entonces estamos en modo de impresion
								* por lo que saltamos
IS_PRNT:	    CMP.B #'p',D1				* SI D1 == 'p', cambiamos flag
			BNE RTI_BUC				* sino, descartamos
P_FOUND: 	    MOVE.B #1,FLG_PRNT			* Si es 'p', cambiamos flag y activamos impresion
			BRA RTI_BUC	
PRNT_MOD: 	   CMP.B #'x',D1				* Si estamos en modo de impresion y encontramos un . cerramos el modo de impresion
			BNE RTI_REC				* Si no hay . , entonces recibimos de forma normal
		   MOVE.B #0,FLG_PRNT			* Si el . esta, cambiamos la flag de impresion a 0 -> Cerramos modo de impresion
			BRA RTI_BUC

* FIN IMPRESIONES

                * Seccion de Tratamiento de Interrupciones: Apartado de Recepcion
RTI_REC:                BSR ESCCAR              * Ejecutamos ESCCAR
                
                        BRA RTI_BUC             * RTI ejecuta concurrentemente y constantemente, ya que es transmision por bloques
                * Seccion de Tratamiento de Interrupciones: Apartado de Transmision
                * Solo se puede transmitir un caracter simultaneamente

RTI_TB:         EOR.L D0,D0				* esto no es necesario :D
		    MOVE.L #PORT_TB,D0              * Cargamos el Identificador del Puerto de Transmision A
                        BSR LEECAR      
                CMP.L #$FFFFFFFF,D0            * El buffer esta vacio: no queda nada por trasmitir
                        BNE RTI_TRAN            * Hacemos la Transmision
                        
                * Si la interrupcion es de “transmision” y el buffer interno de la lınea esta vacıo
                * (la llamada a la funcion LEECAR ha devuelto 0xFFFFFFFF) se deben deshabilitar
                * las interrupciones de transmision para la lınea que ha interrumpido en el registro IMR 
                * Pagina 70 Manual 1.1
                BCLR #TXRDYB,IMRC               * Una vez hacemos la transmision, inhibimos
                MOVE.B IMRC,IMR                 * para evitar llamadas innecesarias.
                        BRA RTI_BUC
RTI_TRAN:       MOVE.B D0,TBB                   * Transmitimos el caracter
                        BRA RTI_BUC              * Volvemos a la RTI en bucle
                * Fin de Transmision de B
RTIEND:         MOVEM.L (A7)+,D0-D2          * Restauramos los registros que habiamos guardado en pila
	          RTE

* Orden de los Buffers
* BUF_RA                 
* BUF_TB          
* FINBUFTB                      * Esto es una direccion unicamente utilizada para localizar el fin del BUFF_TB

LEECAR: MOVEM.L A0-A5,-(A7)     * Se guardan los registros usados en la pila
	  * SELECCION DE BUFFER
	  * Usando BTST, 0 = True, 1 = False
	  BTST #PORT_RA,D0        * Si el bit 0 de D0 = 0 (True) => RA, sino TB
	  	BNE LEE_SELB       
	  MOVE.L #0,A0    	* Tampoco deberia ser necesario hacer esto, pero es para mostrar que se hace reset de los registros de direccion con move   
        LEA BUF_RA,A0           * Cargamos la direccion del Buffer
 	  MOVE.L #0,A1
        MOVE.L PTR_RX,A1       * Cargamos el puntero de extraccion
 	  MOVE.L #0,A2
        MOVE.L PTR_RI,A2       * Cargamos el puntero de insercion
	  MOVE.L #0,A3
        LEA BUF_TB,A3           * Cargamos la direccion en la que termina el buffer (que sera el inicio de la direccion del siguiente)
	  MOVE.L #0,A4
        LEA PTR_RX,A4          * Cargamos la direccion de la variable del puntero de Extraccion
	  MOVE.L #0,A5
        LEA PTR_RI,A5          * Cargamos la direccion de la variable del puntero de Insercion
                BRA LEE_FSEL
LEE_SELB: MOVE.L #0,A0
	  LEA BUF_TB,A0           * Cargamos la direccion del Buffer
	  MOVE.L #0,A1
        MOVE.L PTR_TX,A1       * Cargamos el puntero de extraccion
	  MOVE.L #0,A2
        MOVE.L PTR_TI,A2       * Cargamos el puntero de insercion
	  MOVE.L #0,A3
        LEA FINBUFTB,A3         * Cargamos la direccion en la que termina el buffer
	  MOVE.L #0,A4
        LEA PTR_TX,A4          * Cargamos la direccion de la variable del puntero de Extraccion
	  MOVE.L #0,A5
        LEA PTR_TI,A5          * Cargamos la direccion de la variable del puntero de Insercion

	  * FIN SELECCION BUFFER
LEE_FSEL: EOR.L D0,D0             *
        CMP.L A1,A2            * Si el puntero de extraccion y el de insercion estan 
                BEQ LEEERR      * En la misma posicion, eso quiere decir que el buffer  Esta vacio  
        MOVE.B (A1),D0         * Leemos el caracter desde la posicion del puntero. 
        ADD.L #1,A1            * Incrementamos el puntero (se puede hacer en una sola L con (A1)+ )
        CMP.L A3,A1            * Comprobamos si hemos llegado al final del buffer
                BNE LEESIG      * Si hemos llegado, al tratarse de un buffer circular
        MOVE.L A0,A1           * volvemos a apuntar el ptr extraccion al principio d
LEESIG: MOVE.L A1,(A4)          * Actualizamos el puntero en memoria, mirar ESCCAR para mas info
                BRA LEEEND      *
LEEERR: MOVE.L #$FFFFFFFF,D0    
LEEEND:	MOVEM.L (A7)+,A0-A5 	*Se restauran los registros
	RTS

ESCCAR: MOVEM.L A0-A5/D2,-(A7)  * Se guardan los registros  usados en la pila
        * SELECCION DE BUFFER
	  * Usando BTST, 0 = True, 1 = False
	  BTST #PORT_RA,D0        * Si el bit 0 de D0 = 0 (True) => RA, sino TB
	  	BNE ESC_SELB              
	  MOVE.L #0,A0
        LEA BUF_RA,A0           * Cargamos la direccion del Buffer
	  MOVE.L #0,A1
        MOVE.L PTR_RX,A1       * Cargamos el puntero de extraccion
	  MOVE.L #0,A2
        MOVE.L PTR_RI,A2       * Cargamos el puntero de insercion
	  MOVE.L #0,A3
        LEA BUF_TB,A3           * Cargamos la direccion en la que termina el buffer (que sera el inicio de la direccion del siguiente)
	  MOVE.L #0,A4
        LEA PTR_RX,A4          * Cargamos la direccion de la variable del puntero de Extraccion
	  MOVE.L #0,A5
        LEA PTR_RI,A5          * Cargamos la direccion de la variable del puntero de Insercion
                BRA ESC_FSEL
ESC_SELB: 	  MOVE.L #0,A0
	  LEA BUF_TB,A0         * Cargamos la direccion del Buffer
	  MOVE.L #0,A1
        MOVE.L PTR_TX,A1       * Cargamos el puntero de extraccion
	  MOVE.L #0,A2
        MOVE.L PTR_TI,A2       * Cargamos el puntero de insercion
	  MOVE.L #0,A3
        LEA FINBUFTB,A3         * Cargamos la direccion en la que termina el buffer
	  MOVE.L #0,A4
        LEA PTR_TX,A4          * Cargamos la direccion de la variable del puntero de Extraccion
	  MOVE.L #0,A5
        LEA PTR_TI,A5          * Cargamos la direccion de la variable del puntero de Insercion
        * END

	  * FIN SELECCION BUFFER
ESC_FSEL: EOR.L D0,D0           * Asumimos que la operacion ira bien (D0 = 0, esto solo cambia cuando
                                * haya un error, solo pueden haber 2 valores, 0 o -1 segun el enunciado
        MOVE.B D1,(A2)         * Metemos el caracter de D1 en la direccion del 
        ADD.L #1,A2            * puntero de insercion. Incrementamos puntero (1 sola linea con (A2)+)
        CMP.L A2,A3            * Comprobamos si hemos llegado al final del buffer. 
                BNE ESCSIG      * Buffer Circular -> Cuando se llega al final, se 
        MOVE.L A0,A2           * vuelve a apuntar el ptr_insercion al inicio del buffer.
ESCSIG: CMP.L A2,A1            * Si el puntero de insercion = el de extraccion, entonces
                BEQ ESCERR      * El buffer esta lleno. Es un buffer circular, el ptr_ins 
                                * solo puede ser igual al ptr_ex si ambos estan en la posicion 
                                * inicial. Esto quiere decir que no se ha extraido ningun caracter
                                * y que se han insertado todos los caracteres en el buffer.
        MOVE.L A2,(A5)          * Actualizamos el valor del puntero (al no conservarse el registro
                                * A2, tenemos que hacer una escritura en memoria para que cada vez
                                * que carguemos el puntero este actualizado.
                BRA ESCEND

ESCERR: MOVE.L #$FFFFFFFF,D0    * Si el buffer seleccionado esta lleno
ESCEND:	MOVEM.L (A7)+,A0-A5/D2	* Se restauran los registros
	RTS

SCAN:           LINK  A6,#0     	* Inicializamos marco de pila
                MOVE.L #0,A1             * Reset de los registros utilizados
                MOVE.L 8(A6),A1         * Direccion del Buffer en el que se devuelven
                                        * los caracteres leidos
                EOR.L D2,D2
                MOVE.W 12(A6),D2        * Maximo de caracteres a leer
SIG_SC:         EOR.L D3,D3
                CMP.W #0,D2            * Queremos leer 0 bytes
                        BEQ SCAN_SAL    * nos vamos directamente

SCAN_BUC:       MOVE.L #PORT_RA,D0      * Insertamos el Descriptor de Buffer
                        BSR LEECAR      * Leemos caracter
                CMP.L #$FFFFFFFF,D0    * ERROR: Buffer vacio
                        BEQ SCAN_SAL    * Terminamos: Si el buffer esta vacio no 
                                        * Perdemos mas el tiempo
                MOVE.B D0,(A1)         * Escribimos el caracter leido en el buffer
		    ADD.L #1,A1		    * Incremento de Puntero, se puede hacer en 1 sola L
                ADD.W #1,D3            * Incrementamos el contador
                CMP.W D3,D2             * Hemos leido todos los caracteres?
                        BNE SCAN_BUC    
SCAN_SAL:       MOVE.L D3,D0            * Actualizamos D0 con el valor apropiado
SCAN_END:       UNLK    A6
                RTS

PRINT:          LINK    A6,#0   	        	* Inicializamos marco de pila
                MOVE.L #0,A1                    * Reset de los registros utilizados
                MOVE.L 8(A6),A1                 * Cargamos el buffer
                EOR.L D2,D2
                MOVE.W 12(A6),D2                * Cargamos el tamaño
                EOR.L D3,D3                     * Contador de caracteres = 0

PRNT_BUC:       CMP.W #0,D2                    * Si quedan por transmitir 0 bytes, 
                        BEQ PRNT_INT            * Salimos del bucle de transmision
                MOVE.L #PORT_TB,D0              * Cargamos el descriptor
		    EOR.L D1,D1				* Reset de D1 para almacenar char
                MOVE.B (A1),D1                 * Cargamos el caracter a transmitir
                        BSR ESCCAR              * Escribimos el caracter
                CMP.L #$FFFFFFFF,D0            * ERROR: El buffer está lleno
                        BEQ PRNT_SAL            * Terminamos
                ADD.L #1,A1                     * Incrementamos el A1 solo si no explota
                ADD.W #1,D3                    * Incrementamos el contador
                SUBI.L #1,D2                    * Decrementamos cantidad por transmitir
                        BRA PRNT_BUC
                * Fin del Bucle

                * Zona de Interrupciones
                * Dado que en la RTI cambiamos los bits del IMR
                * para evitar redundancia y los problemas que 
                * Conllevaria, lo que debemos hacer aqui es 
                * actualizarlos cada vez que se vaya a transmitir algo.
                * Para evitar problemas, debemos asegurarnos de que no surge
                * ningun tipo de interrupcion en este momento, ya que esto
                * dispararia la RTI y podria inhibir un bit, provocando una 
                * condicion de carrera que impediria la correcta transmision
                * de caracteres.
PRNT_INT:       EOR.L D6,D6                     * Reset de D6
                MOVE.W SR,D6                    * Salvaguardado de Registro de Estado
                MOVE.W #$2700,SR                * Inhibimos interrupciones
                * Por nuestra simplificacion solo sera TB
                BSET #TXRDYB,IMRC
                        BRA PRNT_ACT
PRNT_ACT:       MOVE.B IMRC,IMR                 * Actualizamos la mascara de interrupcion
                                                * para tener en cuenta las interrupciones 
                                                * por transmision
                MOVE.W D6,SR                    * Restauramos las interrupciones
                * FIN DE ZONA DE INTERRUPCIONES
PRNT_SAL:       MOVE.L D3,D0
PRNT_END:       UNLK    A6
                RTS

* Buffer con los numeros 0123456789 para escribirlo en bucle
BUFNUM: DC.B    '01234567890123456789012345678901234567890123456789012345678901234567890123456789'
		  DC.B	 '01234567890123456789012345678901234567890123456789012345678901234567890123456789'
LENP2:  DC.L    100     * Longitud de este buffer


* FOR I = 0 ... 22
* FOR J = 0 ... 100 (LENP2)

* 2200 caracteres / 100 chars por bloque numerico = 22
PRUEBA:         AND.L #0,D4             * Cantidad de Escrituras
                MOVE.L #22,D2           * Cargamos la cantidad de veces que debemos
                                        * Ejecutar el bloque (220) (i)
		    LEA BUF_RA,A6           * Solo para debugging cargamos al direccion para tenerla facilmente accesible :)
B1PRUEBA:       LEA BUFNUM,A0           * Cargamos la direccion del buffer numerico
                MOVE.L LENP2,D3         * Cargamos la longitud del buffer numerico (j)
B2PRUEBA:       MOVE.L #PORT_RA,D0      * Pasamos el puerto al registro
                MOVE.B (A0)+,D1         * Cargamos el char correspondiente. Aumentamos buffer.
                        BSR ESCCAR      * Escribimos el char con ESCCAR
                CMP.L #$FFFFFFFF,D0    * Si hubo un error, lo marcamos
                        BEQ FIN_PR  
                ADD.L #1,D4            * Aumentamos en 1 la cantidad de escrituras por ESCCAR
                SUB.L #1,D3             * j-- 
                CMP.L #0,D3             * Recorremos el buffer numerico
                        BNE B2PRUEBA     
                SUB.L #1,D2             * i--
                CMP.L #0,D2             * Realizamos el proceso D2 veces
                        BNE B1PRUEBA    
FIN_PR:                 RTS
