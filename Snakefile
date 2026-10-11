container: "docker://docker.io/reanahub/reana-env-root6:6.38.00"

PLOTS = [
    "hp_NNp", "hk_NNk", "hpi_NNpi",
    "hr", "hr_ptbinned", "hz", "hz_ptbinned", "hjt", "hjt_ptbinned",
]


rule all:
    input:
        expand("output/{sample}{plot}.pdf", sample=["", "tagged/"], plot=PLOTS),
        "output/compare/hz_tagged_compare.pdf"


rule analyse:
    input:
        "JFF.C"
    output:
        "output/JFF_hists.root",
        expand("output/{plot}.pdf", plot=PLOTS)
    shell:
        "root -l -b -q {input:q}"


rule analyse_tagged:
    input:
        "JFF_tagged.C"
    output:
        "output/tagged/JFF_hists.root",
        expand("output/tagged/{plot}.pdf", plot=PLOTS)
    shell:
        "root -l -b -q {input:q}"


rule compare:
    input:
        macro="JFF_compare.C",
        dijets="output/JFF_hists.root",
        tagged="output/tagged/JFF_hists.root"
    output:
        "output/compare/hz_tagged_compare.pdf"
    shell:
        "root -l -b -q {input.macro:q}"
