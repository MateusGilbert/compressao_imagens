CC=g++
LD=g++
CFLAGS= -c -Wall --std=c++17 -O3 #-g
LFLAGS= -o

.c.o:
	$(CC) $(CFLAGS) $<

.cpp.o:
	$(CC) $(CFLAGS) $<

Q_OBJS = quantize.o hand_bands.o
COM_OBJS = hand_img.o sub.o fqmf16AA.o fqmf16AS.o
Tr_OBJS = gen_codebooks.o vectorize.o lbg.o $(Q_OBJS) $(COM_OBJS)
EV_OBJS = eval_cdbook.o $(Q_OBJS) $(COM_OBJS)
CF_OBJS = g_cumulative_freqs.o $(Q_OBJS) $(COM_OBJS)
E_OBJS = encode.o $(COM_OBJS) $(Q_OBJS) artcoding_helper.o bit_output.o arithmetic_encode.o #adaptive_model.o
D_OBJS = decode.o $(COM_OBJS) $(Q_OBJS) artcoding_helper.o bit_input.o arithmetic_decode.o #adaptive_model.o
H_OBJS = helper.o $(COM_OBJS)

EXECS = encode decode eval_cdbook train get_cfreqs
T_EXECS = test_subc eval_q test_q test_pad

all: $(EXECS)

encode: $(E_OBJS)
	$(LD) $(LFLAGS) $@ $^

decode: $(D_OBJS)
	$(LD) $(LFLAGS) $@ $^

eval_cdbook: $(EV_OBJS)
	$(LD) $(LFLAGS) $@ $^

train: $(Tr_OBJS)
	$(LD) $(LFLAGS) $@ $^

get_cfreqs: $(CF_OBJS)
	$(LD) $(LFLAGS) $@ $^

test_subc: $(H_OBJS)
	$(LD) $(LFLAGS) $@ $^

#programas para testar as funcoes
test_q: aux_quant.o vectorize.o lbg.o $(Q_OBJS) $(COM_OBJS)
	$(LD) $(LFLAGS) $@ $^

eval_q: eval_quant.o $(Q_OBJS) $(COM_OBJS)
	$(LD) $(LFLAGS) $@ $^

test_pad: aux_pad.o hand_img.o
	$(LD) $(LFLAGS) $@ $^

clean:
	rm -f *.o $(EXECS) $(T_EXECS)
